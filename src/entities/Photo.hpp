#pragma once

#include <json.hpp>

namespace CppTelegramBots {
    class Photo {
    public:
        std::string fileId;

        int fileSize{};
        int width{};
        int height{};

        Photo() = default;
    };

    void from_json(nlohmann::json json, Photo& photo) {
        json.at("file_id").get_to(photo.fileId);
        json.at("file_size").get_to(photo.fileSize);
        json.at("width").get_to(photo.width);
        json.at("height").get_to(photo.height);
    }
}