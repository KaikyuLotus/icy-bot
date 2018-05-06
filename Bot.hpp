#pragma once
#include <JSON/json.hpp>
using json = nlohmann::json;

#include "Methods.hpp"
#include "Utils.hpp"
#include "Photo.hpp"
#include "User.hpp"
#include "Chat.hpp"
#include "Message.hpp"
#include "Update.hpp"



class Bot : public Methods {
	std::string botToken;

	void (*updateHandlerFoo)(Bot, Update);
	void(*commandHandlerFoo)(Bot, Update, std::vector<std::string>);

	std::vector<std::pair<std::string, void(*)(Bot, Update, std::vector<std::string>)>> commandHandlers {
		std::vector<std::pair<std::string, void(*)(Bot, Update, std::vector<std::string>)>>()
	};

	bool stop{ false };

public:
	
	long ID;
	long offset = 0;

	std::string name{ "" };
	std::string username{ "" };
	
	Bot(std::string token) : Methods (token){
		botToken = token;
		
		json jresult = getMe().fire()
							  .getResult()
						      .asJson();

		if (!jresult["ok"].get<bool>()) {
			Log::Error("Something went wrong...");
			Log::Error(jresult["result"].get<std::string>());
			return;
		}

		jresult = jresult["result"];
		ID = jresult["id"].get<long>();
		name = jresult["first_name"].get<std::string>();
		username = jresult["username"].get<std::string>();
	}

	void addCommandHandler(std::string command, void(*commandHandler)(Bot, Update, std::vector<std::string>)) {
		commandHandlers.push_back(std::pair<std::string, void(*)(Bot, Update, std::vector<std::string>)>{ "/" + command, commandHandler });		
	}

	void setUpdateHandler(void (*updateHandler)(Bot, Update)) {
		updateHandlerFoo = updateHandler;
	}

	void startPolling() {
		while (!stop) {
			json::array_t updates = getUpdates().add("timeout", 120)
												.add("offset", offset)
												.fire()
												.getResult()
												.asJsonArray("result");

			for (unsigned int i{ 0 }; i < updates.size(); i++) {
				
				offset = updates[i]["update_id"].get<long>() + 1;

				try {
					Update update = Update(updates[i].get<json>());

					if (startsWith(update.message.text, "/")) {
						std::vector<std::string> parts = split(update.message.text);

						for (int i{ 0 }; i < commandHandlers.size(); i++) {
							if (commandHandlers[i].first == parts[0]) {
								commandHandlers[i].second(*this, update, parts);
								break;
							}
						}
					}
					if (updateHandlerFoo != NULL)
						updateHandlerFoo(*this, update);
				}
				catch (json::type_error e) {
					std::cout << e.what() << std::endl;
				}
			}
		}
		getUpdates().fire();
	}

	void stopPolling() { stop = true; }

};
