#include <iostream>
#include <string>
#include <stdio.h> 
#include <JSON/json.hpp>
#include <time.h>


#include "Utils.hpp"
#include "Bot.hpp"
// Other includes moved to Bot.hpp

using json = nlohmann::json;

json dialogs;
json triggers;

int masterID{ 52962566 }; // Your Telegram ID here

enum triggerType {
	INTERACTION = 0,
	EQUAL = 1,
	CONTENT = 2,
	ETERACTION = 3
};

std::string replaceDummies(std::string string, Update update) {
	replaceAll(&string, "+nome+", update.message.user.name);
	replaceAll(&string, "+username+", update.message.user.username);
	replaceAll(&string, "+snome+", update.message.user.last_name);
	replaceAll(&string, "+uid+", std::to_string(update.message.user.userID));

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

	return "";
}

void elaborateReply(std::string reply, Bot bot, Update update) {
	if (startsWith(reply, "[img]->")) {
		bot.sendChatAction(update.message.chat.chatID, UPLOAD_PHOTO).fire();
		bot.sendPhoto(update.message.chat.chatID, splitByString(reply, "->")[1]).fire();
		return;
	}

	bot.sendChatAction(update.message.chat.chatID, TYPING).fire();
	bot.sendMessage(update.message.chat.chatID, replaceDummies(reply, update)).fire();

	return;
}

void updateHandler(Bot bot , Update update) {

	// Create 'reply' just one time
	std::string reply = "";

	// Reload triggers on every message
	dialogs = json::parse(readFile("resources/JSON/dialogs.json"));
	triggers = json::parse(readFile("resources/JSON/triggers.json"));

	// Check if the bot has been called
	if (lowerCase(update.message.text) == lowerCase(bot.name)) {
		json::array_t replies = dialogs["call"];
		bot.sendChatAction(update.message.chat.chatID, TYPING).fire();
		bot.sendMessage(update.message.chat.chatID, replaceDummies(replies[rand() % replies.size()], update)).fire();
		Log::Action(std::string{ update.message.user.name + " called " + bot.name});
		return;
	}

	// Iterate the triggers, this will be improved in the future
	// If the message starts or ends with the bot's name
	if (startsWith(lowerCase(update.message.text), lowerCase(bot.name)) || endsWith(lowerCase(update.message.text), lowerCase(bot.name))) {
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

// Get the fileID of an image
void imageID(Bot bot, Update update, std::vector<std::string> args) {
	// First let's start typing...
	bot.sendChatAction(update.message.chat.chatID, TYPING).fire();

	// Check if the message is a reply
	if (!update.message.isReply) {
		bot.sendMessage(update.message.chat.chatID, "Please answer a message.").fire();
		return;
	}

	// Check if the message contains an image
	if (update.replyTo.photosSize == 0) {
		bot.sendMessage(update.message.chat.chatID, "Please answer a message that contains an image.").fire();
		return;
	}

	// Take the last one (the largest one)
	Photo photo = update.replyTo.photos[update.replyTo.photosSize - 1];
	bot.sendMessage(update.message.chat.chatID,
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
void start(Bot bot, Update update, std::vector<std::string> args) {
	bot.sendChatAction(update.message.chat.chatID, TYPING).fire();
	bot.sendMessage(update.message.chat.chatID, "Don't start me like that, you make me file like a...bot.").fire();
	Log::Action(update.message.user.username + " '/start'");
}

// Get your ID with /myid
void myid(Bot bot, Update update, std::vector<std::string> args) {
	bot.sendChatAction(update.message.chat.chatID, TYPING);
	bot.sendMessage(update.message.chat.chatID, "ID: " + std::to_string(update.message.user.userID));
}

// Example of only-master command
void stop(Bot bot, Update update, std::vector<std::string> args) {
	bot.sendChatAction(update.message.chat.chatID, TYPING);

	if (masterID != update.message.user.userID) {
		bot.sendMessage(update.message.chat.chatID, "Only my master can issue this command.");
		return;
	} 

	bot.sendMessage(update.message.chat.chatID, "Stopping...").fire();
	bot.stopPolling();
}

void helloWorld(Bot bot, Update update, std::vector<std::string> args) {
	int messageID = update.message.messageID;
	long long chatID = update.message.chat.chatID;

	bot.sendChatAction(chatID, TYPING);

	bot.sendMessage(chatID, "*Hello World*")
		.add(Arguments::parseMode, Arguments::markdown)
		.add(Arguments::replyToMessage, messageID)
		.fire();

	Log::Action("@" + update.message.user.username + " used '/helloWorld'");
}

int main() {
	// Initialize random.
	srand(time(NULL));

	// Read our files
	dialogs = json::parse(readFile("resources/JSON/dialogs.json"));
	triggers = json::parse(readFile("resources/JSON/triggers.json"));

	// Create your bots!
	Bot bot1 = Bot("TOKEN");
	Bot bot2 = Bot("TOKEN");
	
	// Add the updates handler, this handler will receive every update
	bot1.setUpdateHandler(&updateHandler);
	bot2.setUpdateHandler(&updateHandler);

	// Add some handlers just to bot1
	bot1.addCommandHandler("start", &start);
	bot1.addCommandHandler("myid", &myid);
	bot1.addCommandHandler("stop", &stop);
	bot1.addCommandHandler("imageID", &imageID);

	// Add /helloWorld to both bots
	bot1.addCommandHandler("helloWorld", &helloWorld);
	bot2.addCommandHandler("helloWorld", &helloWorld);

	// Start polling for both bots
	Log::Debug("Starting polling...");
	bot1.startPolling(true);
	bot2.startPolling(true);

	/* startPolling is not blocking
	   So we need to do something or the program will close
	   If you don't have a blocking function to execute then just call idle()*/
	bot1.idle();

	return 0;
}