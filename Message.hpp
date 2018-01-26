#pragma once

class Message {

public:
	Chat chat;
	User user;
	
	std::vector<Photo> photos;
	int photosSize{ 0 };

	std::string text{ "" };

	Message() {}

	Message(json message) {
		// std::cout << message.dump() << std::endl;
		if (message["text"].is_string()) {
			text = message["text"].get<std::string>();
		}

		chat = Chat(message["chat"].get<json>());
		user = User(message["from"].get<json>());
		
		try {
			json::array_t photos_array = message.at("photo").get<json::array_t>();
			photosSize = photos_array.size();
			for (int i{ 0 }; i < photosSize; i++) {
				photos.push_back(Photo(photos_array[i]));
			}
			Log::Debug("Photo found!");
		}
		catch (...) {
		}
			
		
	}
};