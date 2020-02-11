#pragma once

namespace CppTelegramBots::Enums {
    enum ParseMode {
        MARKDOWN,
        MARKDOWN_V2,
        HTML
    };

    enum LogLevel {
        DEBUG = 4,
        INFO = 3,
        WARN = 2,
        ERROR = 1,
        SILENT = 0
    };

    const char* asString(ParseMode mode) {
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
