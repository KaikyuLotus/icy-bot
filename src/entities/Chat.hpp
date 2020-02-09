#pragma once

#include <string>

#include <json.hpp>

namespace CppTelegramBots {
    class Chat {
    public:

        long long id{};
        std::string title{};

        Chat() = default;

        explicit Chat(long long id) {
            this->id = id;
        }

    };

    void from_json(const nlohmann::json& json, Chat& chat) {
        json.at("id").get_to(chat.id);

        if (json.count("title") != 0) {
            json.at("title").get_to(chat.title);
        }
    }
}