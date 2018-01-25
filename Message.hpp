#pragma once

using json = nlohmann::json;

class Message {

public:
	Chat chat;
	User user;
	std::string text{ "" };

	Message() {}

	Message(json message) {
		// std::cout << message.dump() << std::endl;
		text = message["text"].get<std::string>();
		chat = Chat(message["chat"].get<json>());
		user = User(message["from"].get<json>());
	}
};