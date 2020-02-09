#pragma once

#include <json.hpp>

#include "Chat.hpp"
#include "User.hpp"
#include "Sticker.hpp"
#include "Photo.hpp"
#include "QuotedMessage.hpp"

namespace CppTelegramBots {
    class Message {
    public:
        int messageId{};

        Chat chat{};
        User user{};
        Sticker sticker{};
        QuotedMessage replyToMessage{}; // Has to be a pointer since it's used in the same class

        std::vector<Photo> photos = std::vector<Photo>();
        std::string text{};

        bool hasText = false;
        bool hasReply = false;
        bool hasSticker = false;

        Message() = default;
    };

    void from_json(const nlohmann::json& json, Message& message) {
        // std::cout << messageJson.dump() << std::endl;

        json.at("chat").get_to(message.chat);
        json.at("from").get_to(message.user);
        json["message_id"].get_to(message.messageId);

        if (json.count("text") != 0) {
            json.at("text").get_to(message.text);
            message.hasText = true;
        }

        if (json.count("reply_to_message") != 0) {
            json.at("reply_to_message").get_to(message.replyToMessage);
            message.hasReply = true;
        }

        if (json.count("sticker") != 0) {
            json.at("sticker").get_to(message.sticker);
            message.hasSticker = true;
        }

        if (json.count("photo") != 0) {
            json.at("photo").get_to(message.photos);
        }
    }
};