#pragma once
#include <CURL/curl.h>
#include "MethodsManager.hpp"

namespace Arguments {
	static constexpr const char* replyToMessage = "reply_to_message_id";
	static constexpr const char* parseMode = "parse_mode";
	static constexpr const char* markdown = "markdown";
};

enum chatAction {
	TYPING = 0,
	UPLOAD_PHOTO = 1,
	UPLOAD_DOCUMENT = 2
};

class Methods : public MethodsManager {

	std::map<int, std::string> chatActions{
		{ TYPING, "typing" },
		{ UPLOAD_PHOTO, "upload_photo" },
		{ UPLOAD_DOCUMENT, "upload_document" }
	};

public:
	
	Methods(std::string token) : MethodsManager(token) {}

	Methods sendMessage(long long chatID, std::string text) {
		setMethod("sendMessage");
		add("chat_id", chatID);
		add("text", text);
		return *this;
	}

	Methods getMe() {
		setMethod("getMe");
		return *this;
	}

	Methods getUpdates() {
		setMethod("getUpdates");
		return *this;
	}

	Methods sendChatAction(long long chatID, chatAction action) {
		setMethod("sendChatAction");
		add("chat_id", chatID);
		add("action", chatActions[action]);
		return *this;
	}

	Methods sendPhoto(long long chatID, std::string fileName, std::string contents) {
		setMethod("sendPhoto");
		add("chat_id", chatID);
		add("photo", fileName, contents);
		return *this;
	}

	Methods sendPhoto(long long chatID, std::string fileID) {
		setMethod("sendPhoto");
		add("chat_id", chatID);
		add("photo", fileID);
		return *this;
	}

	Methods sendDocument(long long chatID, std::string fileName, std::string contents) {
		setMethod("sendDocument");
		add("chat_id", chatID);
		add("document", fileName, contents);
		return *this;
	}

	Methods sendDocument(long long chatID, std::string fileID) {
		setMethod("sendDocument");
		add("chat_id", chatID);
		add("document", fileID);
		return *this;
	}
};