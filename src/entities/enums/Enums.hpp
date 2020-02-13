#pragma once

namespace CppTelegramBots::Enums {

    enum LogLevel {
        DEBUG = 4,
        INFO = 3,
        WARN = 2,
        ERROR = 1,
        SILENT = 0
    };

    enum ParseMode {
        MARKDOWN,
        MARKDOWN_V2,
        HTML
    };

    enum ChatAction {
        TYPING,
        UPLOAD_PHOTO,
        RECORD_VIDEO,
        UPLOAD_VIDEO,
        RECORD_AUDIO,
        UPLOAD_AUDIO,
        UPLOAD_DOCUMENT,
        FIND_LOCATION,
        RECORD_VIDEO_NOTE,
        UPLOAD_VIDEO_NOTE
    };

    std::map<ParseMode, const char *> parseModeMappings{
        {MARKDOWN,    "markdown"},
        {MARKDOWN_V2, "markdown_v2"},
        {HTML,        "html"}
    };

    std::map<ChatAction, const char *> chatActionMappings{
        {TYPING,            "typing"},
        {UPLOAD_PHOTO,      "upload_photo"},
        {RECORD_VIDEO,      "record_video"},
        {UPLOAD_VIDEO,      "upload_video"},
        {RECORD_AUDIO,      "record_audio"},
        {UPLOAD_AUDIO,      "upload_audio"},
        {UPLOAD_DOCUMENT,   "upload_document"},
        {FIND_LOCATION,     "find_location"},
        {RECORD_VIDEO_NOTE, "record_video_note"},
        {UPLOAD_VIDEO_NOTE, "upload_video_note"}
    };

    const char *asString(ParseMode mode) {
        return parseModeMappings[mode];
    }

    const char *asString(ChatAction chatAction) {
        return chatActionMappings[chatAction];
    }


}
