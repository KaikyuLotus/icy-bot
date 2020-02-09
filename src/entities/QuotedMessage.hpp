#pragma once

#include <json.hpp>

#include "Chat.hpp"
#include "User.hpp"
#include "Sticker.hpp"
#include "Photo.hpp"

namespace CppTelegramBots {
    class QuotedMessage {
    public:
        int messageId{};

        Chat chat{};
        User user{};
        Sticker sticker{};

        std::vector<Photo> photos = std::vector<Photo>();
        std::string text{};

        bool hasText = false;
        bool hasSticker = false;

        QuotedMessage() = default;
    };

    void from_json(const nlohmann::json& json, QuotedMessage& message) {
        // std::cout << messageJson.dump() << std::endl;

        json.at("chat").get_to(message.chat);
        json.at("from").get_to(message.user);
        json["message_id"].get_to(message.messageId);

        if (json.count("text") != 0) {
            json.at("text").get_to(message.text);
            message.hasText = true;
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