#pragma once

#include <json.hpp>
#include "Message.hpp"

namespace CppTelegramBots {
    class Update {
    public:
        Message message{};
        long updateId{};

        Update() = default;
    };

    void from_json(nlohmann::json json, Update& update) {
        json["update_id"].get_to(update.updateId);
        json["message"].get_to(update.message);
    }
}