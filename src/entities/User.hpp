#pragma once

#include <json.hpp>

namespace CppTelegramBots {
    class User {
    public:
        long long id{};

        std::string firstName{};
        std::string lastName{};
        std::string username{};

        bool hasUsername = false;
        bool hasLastName = false;

        User() = default;

        User(const long long id, const std::string &firstName, const std::string &username) {
            this->id = id;
            this->firstName = firstName;
            this->username = username;
        }
    };

    void from_json(const nlohmann::json& json, User& user) {
        json.at("id").get_to(user.id);
        json.at("first_name").get_to(user.firstName);

        if (json.count("username") != 0) {
            json.at("username").get_to(user.username);
            user.hasUsername = true;
        }

        if (json.count("last_name") != 0) {
            json.at("last_name").get_to(user.lastName);
            user.hasLastName = true;
        }
    }

}