#pragma once

namespace CppTelegramBots::Enums {
    enum ParseMode {
        MARKDOWN,
        MARKDOWN_V2,
        HTML
    };

    enum LogLevel {
        // 4 debug
        // 3 Info
        // 2 Warn
        // 1 Error
        // Default info
        DEBUG = 4,
        INFO = 3,
        WARN = 2,
        ERROR = 1,
        SILENT = 0
    };

    std::string asString(ParseMode mode) {
        switch (mode) {
            case MARKDOWN:
                return "markdown";
            case MARKDOWN_V2:
                return "markdownv2";
            case HTML:
                return "html";
            default:
                throw std::exception("Unknown parse mode: " + mode);
        }
    }
}
