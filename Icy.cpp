#include <iostream>
#include <string>
#include <stdio.h> 
#include <JSON/json.hpp>

#include "Utils.hpp"
#include "User.hpp"
#include "Chat.hpp"
#include "Message.hpp"
#include "Update.hpp"
#include "Request.hpp"
#include "Bot.hpp"


std::string token = "TOKEN";


void updateHandler(Bot* bot , Update* update) {

	if (lowerCase(update->message.text) == lowerCase(bot->name)) {
		bot->sendChatAction(bot->TYPING, update->message.chat.chatID);
		bot->sendMessage(update->message.chat.chatID, "Dimmi, " + update->message.user.name);
		return;
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

void myid(Bot* bot, Update* update, std::vector<std::string>* args) {
	std::cout << "Command ok" << std::endl;

	bot->sendChatAction(bot->TYPING, update->message.chat.chatID);
	bot->sendMessage(update->message.chat.chatID, "Il tuo ID e': " + std::to_string(update->message.user.chatID));
}


// Dooooon't look at this
void meme(Bot* bot, Update* update, std::vector<std::string>* args) {
	float N1 = std::strtof((*args)[1].c_str(), 0);
	float N2 = std::strtof((*args)[2].c_str(), 0);
	float N3 = std::strtof((*args)[3].c_str(), 0);

	if (N1 > N2 && N1 > N3) {
		bot->sendMessage(update->message.chat.chatID, "Il numero piu' alto e': " + std::to_string(N1));
	}

	if (N2 > N1 && N2 > N3) {
		bot->sendMessage(update->message.chat.chatID, "Il numero piu' alto e': " + std::to_string(N2));
	}

	if (N3 > N2 && N3 > N1) {
		bot->sendMessage(update->message.chat.chatID, "Il numero piu' alto e': " + std::to_string(N3));
	}

	if (N1 == N2 > N3) {
		bot->sendMessage(update->message.chat.chatID, "Il numero piu' alto e': " + std::to_string(N1));
	}

	if (N1 == N2 && N1 == N3 && N2 == N3) {
		bot->sendMessage(update->message.chat.chatID, "I numeri sono uguali!");
	}
}
// Don't!!


int main() {
	Bot bot = Bot(token);
	
	std::cout << "Name:     " << bot.name << std::endl;
	std::cout << "Username: " << bot.username << std::endl;
	std::cout << "ID:       " << bot.ID << std::endl;

	bot.setUpdateHandler(&updateHandler);
	bot.addCommandHandler("/meme", &meme);
	bot.addCommandHandler("/myid", &myid);
	bot.addCommandHandler("/start", &start);
	

	bot.startPolling();

	return 0;
}

