#pragma once
#include <JSON/json.hpp>
using json = nlohmann::json;

#include "Utils.hpp"
#include "Photo.hpp"
#include "User.hpp"
#include "Chat.hpp"
#include "Message.hpp"
#include "Update.hpp"
#include "Request.hpp"


class Bot {
	std::string baseURL = "https://api.telegram.org/bot";
	std::string botToken;
	std::string method = "/getMe";

	void (*updateHandlerFoo)(Bot*, Update*);
	void(*commandHandlerFoo)(Bot*, Update*, std::vector<std::string>*);

	std::vector<std::pair<std::string, void(*)(Bot*, Update*, std::vector<std::string>*)>> commandHandlers
	{
		std::vector<std::pair<std::string, void(*)(Bot*, Update*, std::vector<std::string>*)>>()
	};

	std::map<int, std::string> chatActions{
		{ TYPING, "typing" },
		{ UPLOAD_PHOTO, "upload_photo" },
		{ UPLOAD_DOCUMENT, "upload_document" }
	};


	bool stop{ false };

public:
	enum chatAction {
		TYPING = 0,
		UPLOAD_PHOTO = 1,
		UPLOAD_DOCUMENT = 2
	};

	long ID;
	long offset = 0;

	std::string name{ "" };
	std::string username{ "" };
	
	Bot(std::string token) {
		botToken = token;
		getMe();
	}

	void addCommandHandler(std::string command, void(*commandHandler)(Bot*, Update*, std::vector<std::string>*)) {
		commandHandlers.push_back(std::pair<std::string, void(*)(Bot*, Update*, std::vector<std::string>*)>{ command, commandHandler });		
	}

	void setUpdateHandler(void (*updateHandler)(Bot*, Update*)) {
		updateHandlerFoo = updateHandler;
	}

	void getMe()
	{
		Request req = (baseURL + botToken + "/getMe");
		std::string result = req.fireRequest();

		json jresult = json::parse(result);

		if (!jresult["ok"].get<bool>()) {
			Log::Error("Something went wrong...");
			Log::Error(result);
			return;
		}

		jresult = jresult["result"];
		ID = jresult["id"].get<long>();
		name = jresult["first_name"].get<std::string>();
		username = jresult["username"].get<std::string>();
	}

	std::string sendMessage(long long userID, std::string message) {
		Request req = Request(baseURL + botToken + "/sendMessage");
		req.addParam("text", message);
		req.addParam("chat_id", std::to_string(userID));
		return req.fireRequest();


	}

	void startPolling() {
		while (!stop) {
			json::array_t updates = json::parse(getUpdates())["result"].get<json::array_t>();

			for (unsigned int i{ 0 }; i < updates.size(); i++) {
				
				offset = updates[i]["update_id"].get<long>() + 1;

				try {
					Update update = Update(updates[i].get<json>());
					if (startsWith(update.message.text, "/")) {
						std::vector<std::string> parts = split(update.message.text);

						
						for (int i{ 0 }; i < commandHandlers.size(); i++) {
							if (commandHandlers[i].first == parts[0]) {
								commandHandlers[i].second(this, &update, &parts);
								break;
							}
						}
					}
					if (updateHandlerFoo != NULL)
						updateHandlerFoo(this, &update);
				}
				catch (json::type_error e) {
					std::cout << e.what() << std::endl;
				}
				

			}
		}

		getUpdates(0);
	}

	void stopPolling() {
		stop = true;
	}

	void sendPhoto(long long chatID, const char* photoID) {
		Request img = Request(baseURL + botToken + "/sendPhoto");
		img.addParam("chat_id", std::to_string(chatID));
		img.addParam("photo", photoID);
		img.fireRequest();
	}

	void sendPhoto(long long chatID, std::string fileName) {
		Request img = Request(baseURL + botToken + "/sendPhoto");
		img.addParam("chat_id", std::to_string(chatID));
		img.firePOST(fileName, "photo");
	}

	void sendDocument(long long chatID, std::string fileName) {
		Request img = Request(baseURL + botToken + "/sendDocument");
		img.addParam("chat_id", std::to_string(chatID));
		img.firePOST(fileName, "document");
	}

	void sendChatAction(chatAction action, long long chatID) {
		Request req = Request(baseURL + botToken + "/sendChatAction");
		req.addParam("action", chatActions[action]);
		req.addParam("chat_id", std::to_string(chatID));
		req.fireRequest();

	}

	std::string getUpdates() {
		Request req = Request(baseURL + botToken + "/getUpdates");
		req.addParam("timeout", "120"); // lo sostituirò con una variabile a livello di classe
		req.addParam("offset", std::to_string(offset));
		return req.fireRequest();
	}

	std::string getUpdates(int timeout) {
		Request req = Request(baseURL + botToken + "/getUpdates");
		req.addParam("timeout", std::to_string(timeout)); // lo sostituirò con una variabile a livello di classe
		req.addParam("offset", std::to_string(offset));
		return req.fireRequest();
	}
};
