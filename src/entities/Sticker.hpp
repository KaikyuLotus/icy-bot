#pragma once

#include <json.hpp>
#include <utility>

namespace CppTelegramBots {
    class Sticker {
    public:

        std::string fileId{};
        std::string emoji{};
        std::string setName{};

        int fileSize{};
        int height{};
        int width{};

        Sticker() = default;
    };

    void from_json(nlohmann::json json, Sticker& sticker) {
        json.at("file_id").get_to(sticker.fileId);
        json.at("emoji").get_to(sticker.emoji);
        json.at("set_name").get_to(sticker.setName);
        json.at("file_size").get_to(sticker.fileSize);
        json.at("height").get_to(sticker.height);
        json.at("width").get_to(sticker.width);
    }
}

