#pragma once

#include <string>
#include <iostream>
#include <utility>


namespace CppTelegramBots::Log {

    void applyCout(const std::string &text, const std::string &type) {
        std::cout <<  "[ " << type << " ] - " << text << std::endl;
    }

    void Debug(const std::string &text) {
        applyCout(text, "Debug ");
    }

    void Info(const std::string &text) {
        applyCout(text, "Info  ");
    }

    void Warn(const std::string &text) {
        applyCout(text, "Warn  ");
    }

    void Error(const std::string &text) {
        applyCout(text, "Error ");
    }
}