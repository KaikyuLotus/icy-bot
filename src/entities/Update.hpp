#pragma once

#include <json.hpp>
#include "Message.hpp"
#include "Poll.hpp"

namespace CppTelegramBots {
    class Update {
    public:
        Message message{};
        Poll poll{};
        long updateId{};

        Update() = default;
    };

    void from_json(nlohmann::json json, Update& update) {
        json["update_id"].get_to(update.updateId);
        if (json.count("message") != 0) {
            json.at("message").get_to(update.message);
        }
        if (json.count("poll") != 0) {
            json.at("poll").get_to(update.poll);
        }
    }
}