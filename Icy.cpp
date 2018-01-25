#include <iostream>
#include <string>
#include <stdio.h> 
#include <JSON/json.hpp>
#include <time.h>

#include "Utils.hpp"
#include "User.hpp"
#include "Chat.hpp"
#include "Message.hpp"
#include "Update.hpp"
#include "Request.hpp"
#include "Bot.hpp"

using json = nlohmann::json;

std::string token = "TOKEN";

json dialogs;
json triggers;

void updateHandler(Bot* bot , Update* update) {
	if (update->message.text == "") return;

	if (lowerCase(update->message.text) == lowerCase(bot->name)) {
		bot->sendChatAction(bot->TYPING, update->message.chat.chatID);
		bot->sendMessage(update->message.chat.chatID, "Dimmi, " + update->message.user.name);
		Log::Action(std::string{ update->message.user.name + " called " + bot->name});
		return;
	}

	for (json::iterator it = triggers.begin(); it != triggers.end(); ++it) {
		json::array_t triggers = it.value().get<json::array_t>();
		for (int i{ 0 }; i < triggers.size(); i++) {
			if (contains(update->message.text, triggers[i].get<std::string>())) {
				json::array_t replies = dialogs[triggers[i].get<std::string>()].get<json::array_t>();
				bot->sendChatAction(bot->TYPING, update->message.chat.chatID);
				bot->sendMessage(update->message.chat.chatID, replies[rand() % replies.size()]);
				Log::Action(std::string{ update->message.user.name + ": '" + triggers[i].get<std::string>() + "'."});
				return;
			}
		}
		// Log::Debug(it.value());
	}

	if (startsWith(update->message.text, bot->name)) {
		if (contains(update->message.text, "image", true)) {
			bot->sendChatAction(bot->UPLOAD_PHOTO, update->message.chat.chatID);
			bot->sendPhoto(update->message.chat.chatID, "Icy.jpg");
			return;
		}

		if (contains(update->message.text, "document", true)) {
			bot->sendChatAction(bot->UPLOAD_DOCUMENT, update->message.chat.chatID);
			bot->sendDocument(update->message.chat.chatID, "Icy.jpg");
			return;
		}
	}
}

void start(Bot* bot, Update* update, std::vector<std::string>* args) {
	bot->sendChatAction(bot->TYPING, update->message.chat.chatID);
	bot->sendMessage(update->message.chat.chatID, "Salve " + update->message.user.name);
}

void reload(Bot* bot, Update* update, std::vector<std::string>* args) {
	dialogs = json::parse(readFile("JSON/dialogs.json"));
	triggers = json::parse(readFile("JSON/triggers.json"));

	bot->sendChatAction(bot->TYPING, update->message.chat.chatID);
	bot->sendMessage(update->message.chat.chatID, "Reloaded.");

	Log::Action(std::string{ update->message.user.name + ": 'reload'." });
}


int main() {
	srand(time(NULL));

	dialogs = json::parse(readFile("JSON/dialogs.json"));
	triggers = json::parse(readFile("JSON/triggers.json"));

	Bot bot = Bot(token);
	Log::Info(std::string{ "Bot " + bot.name + " started." });

	bot.setUpdateHandler(&updateHandler);
	bot.addCommandHandler("/reload", &reload);
	bot.addCommandHandler("/start", &start);
	
	Log::Debug("Starting polling...");
	bot.startPolling();

	return 0;
}

