#pragma once

#include <string>
#include <iostream>
#include <utility>
#include <entities/enums/Enums.hpp>

namespace CppTelegramBots::Log {

    std::string getEnvVar(std::string const &key) noexcept {
        char * val = std::getenv(key.c_str());
        return val == NULL ? std::string("") : std::string(val);
    }

    int getLogLevel() noexcept {
        std::string level = getEnvVar("CPP_TELEGRAM_BOTS_LOG_LEVEL").c_str();
        if (level == "") return Enums::LogLevel::SILENT;
        else if (level == "DEBUG") return Enums::LogLevel::DEBUG;
        else if (level == "INFO") return Enums::LogLevel::INFO;
        else if (level == "WARN") return Enums::LogLevel::WARN;
        else if (level == "ERROR") return Enums::LogLevel::ERROR;
        else if (level == "SILENT") return Enums::LogLevel::SILENT;
        else {
            std::cout << "Unrecognized log level '" << level << "' using SILENT as default" << std::endl;
            return Enums::LogLevel::SILENT;
        }

    }

    int logLevel = getLogLevel();

    void applyCout(const std::string &text, const std::string &type) {
        std::cout <<  "[ " << type << " ] - " << text << std::endl;
    }

    void Debug(const std::string &text) {
        if (logLevel < Enums::LogLevel::DEBUG) return;
        applyCout(text, "Debug ");
    }

    void Info(const std::string &text) {
        if (logLevel < Enums::LogLevel::INFO) return;
        applyCout(text, "Info  ");
    }

    void Warn(const std::string &text) {
        if (logLevel < Enums::LogLevel::WARN) return;
        applyCout(text, "Warn  ");
    }

    void Error(const std::string &text) {
        if (logLevel < Enums::LogLevel::ERROR) return;
        applyCout(text, "Error ");
    }
}