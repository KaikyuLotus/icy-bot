#pragma once

class Message {

public:
	Chat chat;
	User user;

	bool isReply = false;

	std::vector<Photo> photos;
	int photosSize{ 0 };
	int messageID;

	std::string text{ "" };

	Message() {}

	Message(json message) {
		// std::cout << message.dump() << std::endl;
		if (message["text"].is_string()) {
			text = message["text"].get<std::string>();
		}

		chat = Chat(message["chat"].get<json>());
		user = User(message["from"].get<json>());

		messageID = message["message_id"].get<int>();

		if (message.find("reply_to_message") != message.end())
			isReply = true;

		try {
			json::array_t photos_array = message.at("photo").get<json::array_t>();
			photosSize = photos_array.size();
			for (int i{ 0 }; i < photosSize; i++) {
				photos.push_back(Photo(photos_array[i]));
			}
		}
		catch (...) {
		}
			
		
	}
};