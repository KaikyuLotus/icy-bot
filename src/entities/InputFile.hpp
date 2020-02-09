#pragma once

#include <json.hpp>

namespace CppTelegramBots {
    class InputFile {
    public:
        std::string name{};
        const std::string *content{};

        InputFile(const std::string &name, const std::string *content) {
            this->name = name;
            this->content = content;
        }
    };

}