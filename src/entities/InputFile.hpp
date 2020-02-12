#pragma once

#include <json.hpp>
#include <utility>

namespace CppTelegramBots {
    class InputFile {
    public:
        std::string name{};
        std::string content{};

        InputFile(std::string name, std::string content) {
            this->name = name;
            this->content = std::move(content);
        }
    };

}