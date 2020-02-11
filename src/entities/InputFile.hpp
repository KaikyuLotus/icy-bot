#pragma once

#include <json.hpp>

namespace CppTelegramBots {
    class InputFile {
    public:
        const char* name{};
        const std::string *content{};

        InputFile(const char* name, const std::string *content) {
            this->name = name;
            this->content = content;
        }
    };

}