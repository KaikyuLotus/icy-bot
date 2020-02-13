#pragma once

#include <json.hpp>
#include <utility>
#include "PhotoSize.hpp"

namespace CppTelegramBots {
    class UserProfilePhotos {
    public:

        int totalCount{};
        std::vector<std::vector<PhotoSize>> photos{};

        UserProfilePhotos() = default;
    };

    void from_json(nlohmann::json json, UserProfilePhotos& userProfilePhotos) {
        json.at("total_count").get_to(userProfilePhotos.totalCount);
        json.at("photos").get_to(userProfilePhotos.photos);
    }
}
