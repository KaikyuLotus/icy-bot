#include <iostream>
#include <string>
#include <stdio.h> 
#include <JSON/json.hpp>

#include "Bot.hpp"
#include "Requests.hpp"
#include "Utils.hpp"
#include "Meteo.hpp"

using json = nlohmann::json;

json dialogs;
json triggers;

int masterID{ 487353090 }; // Your Telegram ID here

enum triggerType {
	INTERACTION = 0,
	EQUAL = 1,
	CONTENT = 2,
	ETERACTION = 3
};

// Actually i don't know if this is a nice solution
std::string replaceDummies(std::string string, Update update) {
	// Replace the dummy in the string with another string 
	replaceAll(&string, "+nome+", update.message.user.name);
	replaceAll(&string, "+username+", update.message.user.username);
	replaceAll(&string, "+snome+", update.message.user.last_name);
	replaceAll(&string, "+uid+", std::to_string(update.message.user.userID));

	// Check these dummies only if the message is a reply
	if (update.message.isReply) {
		replaceAll(&string, "+nome2+", update.replyTo.user.name);
		replaceAll(&string, "+username2+", update.replyTo.user.username);
		replaceAll(&string, "+snome2+", update.replyTo.user.last_name);
		replaceAll(&string, "+uid2+", std::to_string(update.replyTo.user.userID));
	}

	return string;
}

std::string findReply(triggerType type, std::string message, json currentTriggers) {
	for (json::iterator it = currentTriggers.begin(); it != currentTriggers.end(); it++) {
		json::array_t triggers = it.value().get<json::array_t>();
		for (unsigned int i{ 0 }; i < triggers.size(); i++) {
			switch (type) {
				// This is a bit weird but still a clean solution i guess...
				case INTERACTION:
					if (!contains(lowerCase(message), lowerCase(triggers[i].get<std::string>()))) continue;
					break;

				case EQUAL:
					if (lowerCase(message) != lowerCase(triggers[i].get<std::string>())) continue;
					break;

				case CONTENT:
					if (!(lowerCase(message) != lowerCase(triggers[i].get<std::string>()) && contains(lowerCase(message), lowerCase(triggers[i].get<std::string>())))) continue;
					break;

				case ETERACTION:
					if (!contains(lowerCase(message), lowerCase(triggers[i].get<std::string>()))) continue;
					break;
			}

			json::array_t replies{ dialogs[it.key()].get<json::array_t>() };
			Log::Action(std::string{ "'" + it.key() + "' used." });
			return replies[rand() % replies.size()];
		}
	}

	// No reply needed
	return "";
}

void elaborateReply(std::string reply, Bot* bot, Update update) {
	// If the message starts with [img]-> then we have a photo fileID
	if (startsWith(reply, "[img]->")) {
		bot->sendChatAction(update.message.chat.chatID, UPLOAD_PHOTO).fire();
		bot->sendPhoto(update.message.chat.chatID, splitByString(reply, "->")[1]).fire();
		return;
	}

	if (startsWith(reply, "[stk]->")) {
		bot->sendSticker(update.message.chat.chatID, splitByString(reply, "->")[1]).fire();
		return;
	}

	bot->sendChatAction(update.message.chat.chatID, TYPING).fire();
	bot->sendMessage(update.message.chat.chatID, replaceDummies(reply, update)).fire();
	return;
}

// Notice that we need the pointer to bot, it's important
// Often we neet to change values to the ORIGINAL copy of Bot
// So we actually need the pointer of it
void updateHandler(Bot* bot, Update update) {
	// Create 'reply' just one time
	std::string reply = "";

	// Reload triggers on every message
	dialogs = json::parse(readFile("resources/JSON/dialogs.json"));
	triggers = json::parse(readFile("resources/JSON/triggers.json"));

	// Check if the bot has been called
	if (lowerCase(update.message.text) == lowerCase(bot->name)) {
		json::array_t replies = dialogs["call"];
		bot->sendChatAction(update.message.chat.chatID, TYPING).fire();
		bot->sendMessage(update.message.chat.chatID, replaceDummies(replies[rand() % replies.size()], update)).fire();
		Log::Action(std::string{ update.message.user.name + " called " + bot->name});
		return;
	}

	// Iterate the triggers, this will be improved in the future
	// If the message starts or ends with the bot's name
	if (startsWith(lowerCase(update.message.text), lowerCase(bot->name)) || endsWith(lowerCase(update.message.text), lowerCase(bot->name))) {
		if (update.message.isReply)
			reply = findReply(ETERACTION, update.message.text, triggers["eteractions"].get<json>());
		else
			reply = findReply(INTERACTION, update.message.text, triggers["interactions"].get<json>());

		if (reply != "")
			return elaborateReply(reply, bot, update);
		return;
	}
	
	reply = findReply(EQUAL, update.message.text, triggers["equals"].get<json>());
	if (reply != "") return elaborateReply(reply, bot, update);

	reply = findReply(CONTENT, update.message.text, triggers["contents"].get<json>());
	if (reply != "") return elaborateReply(reply, bot, update);
}

// If we do something wrong this function helps us to debug the problem
void errorHandler(Bot* bot, Update update, std::string func, std::string error) {
	std::string msg1 = "Handled error: '" + error + "' in command '" + func + "'";
	std::string msg2 = "Last error has been caused by:\n'" + update.update_json.dump(2) + "'";
	Log::Error(msg1);
	Log::Debug(msg2);
	bot->sendChatAction(masterID, TYPING).fire();
	bot->sendMessage(masterID, msg1 + "\n" + msg2).fire();
}

// Get the fileID of an image
void imageID(Bot* bot, Update update) {
	// First let's start typing...
	bot->sendChatAction(update.message.chat.chatID, TYPING).fire();

	// Check if the message is a reply
	if (!update.message.isReply) {
		bot->sendMessage(update.message.chat.chatID, "Please answer a message.").fire();
		return;
	}

	// Check if the message contains an image
	if (update.replyTo.photosSize == 0) {
		bot->sendMessage(update.message.chat.chatID, "Please answer a message that contains an image.").fire();
		return;
	}

	// Take the last one (the largest one)
	Photo photo = update.replyTo.photos[update.replyTo.photosSize - 1];
	bot->sendMessage(update.message.chat.chatID,
		  "ID: *" + photo.photoID + "*\n"
		+ "Size: *" + std::to_string(photo.fileSize) + "* kb\n"
		+ "Width: *" + std::to_string(photo.width)   + "* px\n" 
		+ "Height: *" + std::to_string(photo.height) + "* px")
		.add("parse_mode", "markdown") // You can add markdown like this
		.add("reply_to_message_id", std::to_string(update.replyTo.messageID)) // Reply to the image
		.fire(); 
	return;
}

// Just a classic /start command
void start(Bot* bot, Update update) {
	bot->sendChatAction(update.message.chat.chatID, TYPING).fire();
	bot->sendMessage(update.message.chat.chatID, "Don't start me like that, you make me file like a...bot.").fire();
}

// Example of only-master command
void stop(Bot* bot, Update update) {
	bot->sendChatAction(update.message.chat.chatID, TYPING).fire();

	if (masterID != update.message.user.userID) {
		bot->sendMessage(update.message.chat.chatID, "Only my master can issue this command.").fire();
		return;
	} 

	bot->sendMessage(update.message.chat.chatID, "Stopping...").fire();
	bot->stopPolling();
}

// Sample command, here you can see how to add extra arguments to a method
void helloWorld(Bot* bot, Update update) {
	int messageID = update.message.messageID;
	long long chatID = update.message.chat.chatID;

	bot->sendMessage(chatID, "*Hello World in " + std::to_string(bot->getElapsedTime()) + " ns*")
		.add(Arguments::parseMode, Arguments::markdown)
		.add(Arguments::replyToMessage, messageID)
		.fire();
}

// If you're unsure of the structure of some updates, use this command!
void showUpdate(Bot* bot, Update update) {
	bot->sendChatAction(update.message.chat.chatID, TYPING).fire();
	bot->sendMessage(update.message.chat.chatID, update.update_json.dump()).fire();
}

// Command to get the ID of a sticker, so you can add it in some dialogs
void getSticker(Bot* bot, Update update) {
	std::string reply = "";

	bot->sendChatAction(update.message.chat.chatID, TYPING).fire();

	if (!update.message.isReply)
		reply = "Quote a sticker please.";
	else if (!update.replyTo.isSticker)
		reply = "Quote a sticker.";
	else
		reply = "Sticker ID: " + update.replyTo.sticker.fileID;

	bot->sendMessage(update.message.chat.chatID, reply).fire();
}

// Just a function to generate an error, it'll be handled by the Bot
void generateError(Bot* bot, Update update) {
	bot->sendChatAction(update.message.chat.chatID, TYPING).fire();
	bot->sendMessage(update.message.chat.chatID, "Generating error...").fire();
	throw std::overflow_error("Divide by zero exception");
}

// Example of common requests, check Meteo class for more infos
void meteo(Bot* bot, Update update, std::vector<std::string> args) {
	bot->sendChatAction(update.message.chat.chatID, TYPING).fire();

	if (args.size() < 2) {
		bot->sendMessage(update.message.chat.chatID, "Specify a city.").fire();
		return;
	}

	std::string city = "";
	for (unsigned int i = 1; i < args.size(); i++) {
		city += args[i] + " ";
	}
	city.pop_back();

	try {
		ForecastDay day = Meteo().getForecast(city)[0];
		std::string message = "Meteo for *" + city + "*:\nIt's *" + day.condition + "*\n\n*Temperatures*\nLow:  *" + day.low + "*\nHigh: *" + day.high + "*";
		bot->sendMessage(update.message.chat.chatID, message)
			.add(Arguments::parseMode, Arguments::markdown)
			.fire();
	} catch (...) {
		bot->sendMessage(update.message.chat.chatID, "'" + city + "' not found.").fire();
	}

}

int main() {
	// FreeConsole();

	// Initialize random.
	srand(time(NULL));

	// Read our JSON files
	dialogs = json::parse(readFile("resources/JSON/dialogs.json"));
	triggers = json::parse(readFile("resources/JSON/triggers.json"));

	Bot* bot;

	try {
		// Create your bot!
		bot = new Bot(readFile("token.txt"));
	} catch (errors::TokenException& exc) {
		Log::Error("Exception while creating Bot:");
		Log::Error(exc.what());
		Sleep(1000);
		return -1;
	}

	// Add the updates handler, this handler will receive every update
	bot->setUpdateHandler(&updateHandler);
	// Add the errors handler, this handler will notice us in case of problems
	bot->setErrorHandler(&errorHandler);

	// Add some handlers
	bot->addCommandHandler("start", &start);
	bot->addCommandHandler("stop", &stop);
	bot->addCommandHandler("imageID", &imageID);
	bot->addCommandHandler("meteo", &meteo);
	bot->addCommandHandler("helloWorld", &helloWorld);
	bot->addCommandHandler("showUpdate", &showUpdate);
	bot->addCommandHandler("getSticker", &getSticker);
	bot->addCommandHandler("generateError", &generateError);

	// Start polling updates
	bot->startPolling(true);

	/* startPolling is not blocking
	   So we need to do something or the program will close
	   If you don't have a blocking function to execute then just call idle() */
	bot->idle();

	return 0;
}