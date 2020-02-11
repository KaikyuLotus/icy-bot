#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/enums/Enums.hpp>
#include <entities/Message.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SendDocument : public BaseMethod<BaseResponse<Message>> {
    public:
        template <typename T, typename = std::enable_if_t<std::is_same<T, long long>::value || std::is_same<T, const char*>::value>>
        SendDocument(T chatId, const char* document) : BaseMethod("sendDocument") {
            add("chat_id", chatId);
            add("document", document);
        }

        template <typename T, typename = std::enable_if_t<std::is_same<T, long long>::value || std::is_same<T, const char*>::value>>
        SendDocument(T chatId, const InputFile &document) : BaseMethod("sendDocument") {
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




