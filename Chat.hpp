#pragma once

class Chat {

public:
	long long chatID{ 0 };
	std::string title{ "" };

	Chat() {

	}

	Chat(json chat) {
		chatID = chat["id"].get<long long>();

		if (std::find(chat.begin(), chat.end(), "title") != chat.end()) {
			title = chat["title"].get<std::string>();
		}
	}
};