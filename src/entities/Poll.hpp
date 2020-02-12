#pragma once

#include <string>

#include <json.hpp>
#include "PollOption.hpp"

namespace CppTelegramBots {
    class Poll {
    public:

        std::string id{};
        std::string question{};
        std::vector<PollOption> options{};
        int totalVoterCount{};
        bool isClosed{};
        bool isAnonymous{};
        std::string type{};
        bool allowsMultipleAnswers{};

        Poll() = default;
    };

    void from_json(const nlohmann::json& json, Poll& poll) {
        json.at("id").get_to(poll.id);
        json.at("question").get_to(poll.question);
        json.at("options").get_to(poll.options);
        json.at("total_voter_count").get_to(poll.totalVoterCount);
        json.at("is_closed").get_to(poll.isClosed);
        json.at("is_anonymous").get_to(poll.isAnonymous);
        json.at("type").get_to(poll.type);
        json.at("allows_multiple_answers").get_to(poll.allowsMultipleAnswers);
    }
}