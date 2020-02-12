#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

#undef SendMessage

namespace CppTelegramBots {
    class SendMessage : public BaseMethod<BaseResponse<Message>> {
    public:
        template <typename T,
            typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        SendMessage(T chatId, const char* text) : BaseMethod("sendMessage") {
            add("text", text);
            add("chat_id", chatId);
        }

        [[nodiscard]] SendMessage* replyToMessageId(long messageId) {
            add("reply_to_message_id", messageId);
            return this;
        }

        [[nodiscard]] SendMessage* parseMode(Enums::ParseMode parseMode) {
            add("parse_mode", Enums::asString(parseMode));
            return this;
        }
    };
}




