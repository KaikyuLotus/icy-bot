#pragma once

#include <json.hpp>
#include <utility>

namespace CppTelegramBots {
    class PhotoSize {
    public:

        std::string fileId{};
        std::string fileUniqueId{};

        int width{};
        int height{};
        int fileSize{};

        PhotoSize() = default;
    };

    void from_json(nlohmann::json json, PhotoSize& photoSize) {
        json.at("file_id").get_to(photoSize.fileId);
        json.at("file_unique_id").get_to(photoSize.fileUniqueId);
        json.at("width").get_to(photoSize.width);
        json.at("height").get_to(photoSize.height);
        if (json.count("file_size") != 0) {
            json.at("file_size").get_to(photoSize.fileSize);
        }
    }
}

