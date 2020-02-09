#pragma once

namespace CppTelegramBots::Enums {
    enum ParseMode {
        MARKDOWN,
        MARKDOWN_V2,
        HTML
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
