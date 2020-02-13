#pragma once

#include <json.hpp>
#include <utility>
#include "PhotoSize.hpp"

namespace CppTelegramBots {
    class File {
    public:

        std::string fileId{};
        std::string fileUniqueId{};
        std::string filePath{};

        int fileSize{};

        bool hasFileSize{false};
        bool hasFilePath{false};

        File() = default;
    };

    void from_json(nlohmann::json json, File& file) {
        json.at("file_id").get_to(file.fileId);
        json.at("file_unique_id").get_to(file.fileUniqueId);

        if (json.count("file_size") != 0) {
            json.at("file_size").get_to(file.fileSize);
            file.hasFileSize = true;
        }

        if (json.count("file_path") != 0) {
            json.at("file_path").get_to(file.filePath);
            file.hasFilePath = true;
        }
    }
}
