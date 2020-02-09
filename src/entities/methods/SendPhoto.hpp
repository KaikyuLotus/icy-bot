#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/enums/Enums.hpp>
#include <entities/InputFile.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SendPhoto : public BaseMethod<BaseResponse<Message>> {
    public:
        SendPhoto(const char* chatId, const char* photo) : BaseMethod("sendPhoto") {
            add("chat_id", chatId);
            add("photo", photo);
        }

        SendPhoto(long long chatId, const char* photo) : BaseMethod("sendPhoto") {
            add("chat_id", chatId);
            add("photo", photo);
        }

        SendPhoto(const char* chatId, const InputFile &file) : BaseMethod("sendPhoto") {
            add("chat_id", chatId);
            add("photo", file);
        }

        SendPhoto(long long chatId, const InputFile &file) : BaseMethod("sendPhoto") {
            add("chat_id", chatId);
            add("photo", file);
        }

        [[nodiscard]] SendPhoto caption(const char* caption) {
            add("caption", caption);
            return *this;
        }

        // TODO complete enum
        [[nodiscard]] SendPhoto parseMode(Enums::ParseMode parseMode) {
            add("parse_mode", Enums::asString(parseMode).c_str());
            return *this;
        }

        [[nodiscard]] SendPhoto replyToMessageId(long messageId) {
            add("reply_to_message_id", messageId);
            return *this;
        }

    };
}




