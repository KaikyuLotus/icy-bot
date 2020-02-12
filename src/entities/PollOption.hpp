#pragma once

#include <string>

#include <json.hpp>

namespace CppTelegramBots {
    class PollOption {
    public:

        std::string text{};
        int voterCount{};

        PollOption() = default;
    };

    void from_json(const nlohmann::json& json, PollOption& poll) {
        json.at("text").get_to(poll.text);
        json.at("voter_count").get_to(poll.voterCount);
    }
}