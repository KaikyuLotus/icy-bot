#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SendDocument : public BaseMethod<BaseResponse<User>> {
    public:
        SendDocument(const char* chatId, const char* document) : BaseMethod("sendDocument") {
            add("chat_id", chatId);
            add("document", document);
        }

        SendDocument(long long chatId, const char* document) : BaseMethod("sendDocument") {
            add("chat_id", chatId);
            add("document", document);
        }

        [[nodiscard]] SendDocument* caption(const char* caption) {
            add("caption", caption);
            return this;
        }

        [[nodiscard]] SendDocument* parseMode(Enums::ParseMode parseMode) {
            add("parse_mode", Enums::asString(parseMode));
            return this;
        }

        [[nodiscard]] SendDocument* replyToMessageId(long messageId) {
            add("reply_to_message_id", messageId);
            return this;
        }

        [[nodiscard]] SendDocument* thumb(const char* thumb) {
            add("thumb", thumb);
            return this;
        }

        // TODO shold be input file
        [[nodiscard]] SendDocument* thumb(long long &thumb) {
            throw Errors::NotImplementedException("Thumbs are not implemented yet");
        }

    };
}




