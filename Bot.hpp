#pragma once
#include <thread>
#include <chrono>
#include <JSON/json.hpp>
using json = nlohmann::json;

#include "Methods.hpp"
#include "Utils.hpp"
#include "Sticker.hpp"
#include "Photo.hpp"
#include "User.hpp"
#include "Chat.hpp"
#include "Message.hpp"
#include "Update.hpp"
#include "Errors.hpp"


static bool stopProgram = false;

static BOOL WINAPI console_ctrl_handler(DWORD dwCtrlType) {
	if (stopProgram) {
		Log::Debug("Force closing.");
		return FALSE;
	} else {
		stopProgram = true;
		Log::Debug("CTRL-C pressed, stopping all bots.");
	}
	return TRUE;
}

class Bot : public Methods {
public:

	long ID;
	long offset = 0;


	std::string name{ "" };
	std::string username{ "" };
	
	// Constructor
	Bot(std::string token) : Methods (token){
		botToken = token;
		
		json jresult = getMe().fire().getResult().asJson();

		if (!jresult["ok"].get<bool>())
			throw errors::TokenException("'" + token + "' is not a valid token.", token);

		jresult = jresult["result"];
		ID = jresult["id"].get<long>();
		name = jresult["first_name"].get<std::string>();
		username = jresult["username"].get<std::string>();

		SetConsoleCtrlHandler(console_ctrl_handler, TRUE);
		Log::Info(std::string{ "Bot " + name + " started." });
	}

	// Set a command handler function
	void addCommandHandler(std::string command, void(*commandHandler)(Bot* bot, Update update, std::vector<std::string> args)) {
		commandHandlersArgs.push_back(std::pair<std::string, void(*)(Bot* bot, Update update, std::vector<std::string> args)>{ command, commandHandler });		
	}

	void addCommandHandler(std::string command, void(*commandHandler)(Bot* bot, Update update)) {
		commandHandlers.push_back(std::pair<std::string, void(*)(Bot* bot, Update update)>{ command, commandHandler });
	}

	// Set an error handler function
	void setErrorHandler(void(*errorHandler)(Bot* bot, Update update, std::string func, std::string error)) {
		errorHandlerFoo = errorHandler;
	}

	// Set an update handler function
	void setUpdateHandler(void (*updateHandler)(Bot* bot, Update update)) {
		updateHandlerFoo = updateHandler;
	}

	// Start getting updates, if you pass 'true' the you won't get old updates
	void startPolling(bool clean) {
		if (clean) cleanUpdates();
		_startPolling();
	}

	// Start getting updates!
	void startPolling() {
		_startPolling();
	}
	
	// Stop the updates of this bot
	void stopPolling() {
		if (stop) {
			Log::Action("Bot " + name + " already stopped.");
			return;
		}
		stop = true;
		Log::Action("Bot " + name + " stopped.");
	}

	// Use this function if you don't have anything to do else than getting updates
	void idle() {
		while (!stop) {
			Sleep(1);
			if (stopProgram)
				stopPolling();
		}

		// Tell to Telegram that we've read the last update before closing
		getUpdates().add("offset", offset).fire();
	}

	// Default update handler, in case you forget to add an handler at least you don't get a black console
	void defaultUpdateHandlerFoo(Bot* bot, Update update) {
		Log::Debug("Unhandled update #" + std::to_string(update.updateID));
	}

	// Default error handler, prints out some basic informations
	void defaultErrorHandlerFoo(Bot* bot, Update update, std::string func, std::string error) {
		Log::Error("Update '" + update.update_json.dump() + "' caused error " + error + " (in command '" + func + "')");
	}

	int getElapsedTime() {
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - updateStartTime).count();
	}

private:

	bool stop{ false };

	std::string botToken;
	std::string commandSymbol{ "/" };

	std::chrono::steady_clock::time_point updateStartTime;

	// Our handlers
	void(*updateHandlerFoo)(Bot* bot, Update update) { NULL };
	// void(*commandHandlerFoo)(Bot* bot, Update update, std::vector<std::string> args) { NULL };
	void(*errorHandlerFoo)(Bot* bot, Update update, std::string func, std::string error) { NULL };

	std::vector<std::pair<std::string, void(*)(Bot*, Update, std::vector<std::string>)>> commandHandlersArgs{
		std::vector<std::pair<std::string, void(*)(Bot*, Update, std::vector<std::string>)>>()
	};

	std::vector<std::pair<std::string, void(*)(Bot*, Update)>> commandHandlers{
		std::vector<std::pair<std::string, void(*)(Bot*, Update)>>()
	};

	// This function cleans all the pending updates
	void cleanUpdates() {
		// Telegram gives us only the last update using -1
		offset = -1;
		json updates = getUpdates().add("offset", offset).fire().getResult().asJsonArray("result");

		// Check if there are updates to clean
		if (updates.size() > 0) {
			// So we can know what's the last update ID
			offset = updates[0]["update_id"].get<long>() + 1;
			// Now tell to Telegram that we've read the last message
			getUpdates().add("offset", offset).fire();

			Log::Debug("Updates cleaned, offset: " + std::to_string(offset));
		} else
			Log::Debug("No updates to clean.");
	}

	// This function actually starts the polling thread
	void _startPolling() {
		Log::Debug("Starting polling for bot @" + username + "...");
		std::thread updater(&Bot::pollingTask, this);
		updater.detach();
	}

	// Handle every update and choose the right handler for it
	void handleUpdate(Update* update) {
		std::string functionExecuted = "unknown";

		try {

			if (!startsWith(update->message.text, "/")) {
				functionExecuted = "updateHandler";
				if (errorHandlerFoo == NULL)
					defaultUpdateHandlerFoo(this, *update);
				else
					updateHandlerFoo(this, *update);
				return;
			}

			std::vector<std::string> parts = split(update->message.text);

			for (unsigned int i{ 0 }; i < commandHandlers.size(); i++) {
				if (commandSymbol + commandHandlers[i].first != parts[0]) continue;

				functionExecuted = commandHandlers[i].first;
				commandHandlers[i].second(this, *update);
				Log::Action("@" + update->message.user.username + " used '" + commandHandlers[i].first + "'");
				return;
			}

			for (unsigned int i{ 0 }; i < commandHandlersArgs.size(); i++) {
				if (commandSymbol + commandHandlersArgs[i].first != parts[0]) continue;

				functionExecuted = commandHandlersArgs[i].first;
				commandHandlersArgs[i].second(this, *update, parts);
				Log::Action("@" + update->message.user.username + " used '" + commandHandlersArgs[i].first + "'");
				return;
			}

			// Catch all std::exceptions 
		} catch (const std::exception& e) {
			if (errorHandlerFoo == NULL)
				defaultErrorHandlerFoo(this, update->update_json.get<json>(), functionExecuted, e.what());
			else
				errorHandlerFoo(this, update->update_json.get<json>(), functionExecuted, e.what());

			// Catch any other error
		} catch (...) {
			if (errorHandlerFoo == NULL)
				defaultErrorHandlerFoo(this, update->update_json.get<json>(), functionExecuted, "Unknown error...");
			else
				errorHandlerFoo(this, update->update_json.get<json>(), functionExecuted, "Unknown error...");
		}
	}

	// Create the Update from Telegram's JSON, handle sporadic error
	void elaborateUpdates(json::array_t updates) {
		for (unsigned int i{ 0 }; i < updates.size(); i++) {
			Update* update;
			offset = updates[i]["update_id"].get<long>() + 1;

			try {
				update = new Update(updates[i].get<json>());
			} catch (json::type_error e) {
				Log::Error(e.what());
				continue;
			}

			updateStartTime = std::chrono::steady_clock::now();
			handleUpdate(update);
			auto end = std::chrono::steady_clock::now();
			auto elaps = std::chrono::duration_cast<std::chrono::milliseconds>(end - updateStartTime);
			Log::Debug("Update #" + std::to_string(update->updateID) + " handled in " + std::to_string(elaps.count()) + " ms");
		}
	}

	void pollingTask() {
		while (!stop) {
			elaborateUpdates(getUpdates()
				.add("timeout", 120)
				.add("offset", offset)
				.fire()
				.getResult()
				.asJsonArray("result")
			);
		}
	}
};