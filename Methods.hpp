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

	// Here you can create custom base methods

	// Ask for the mandatory arguments
	Methods sendChatAction(long long chatID, chatAction action) {
		// Set the method name
		setMethod("sendChatAction");
		// Add the mandatory arguments
		add("chat_id", chatID);
		add("action", chatActions[action]);
		// Return this so we can add other arguments later!
		return *this;
	}

	Methods sendPhoto(long long chatID, std::string fileName, std::string contents) {
		setMethod("sendPhoto");
		add("chat_id", chatID);
		// If we call this override of 'add' then we're POSTing
		// Everything is automated!
		add("photo", fileName, contents);
		return *this;
	}

	Methods sendPhoto(long long chatID, std::string fileID) {
		setMethod("sendPhoto");
		add("chat_id", chatID);
		add("photo", fileID);
		return *this;
	}

	Methods sendSticker(long long chatID, std::string stickerID) {
		setMethod("sendSticker");
		add("chat_id", chatID);
		add("sticker", stickerID);
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