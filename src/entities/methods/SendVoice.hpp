#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/enums/Enums.hpp>
#include <entities/Message.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SendVoice : public BaseMethod<BaseResponse<Message>> {
    public:
        template <typename T, typename B, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value && TemplateUtils::is_input_file_or_token<B>::value>>
        SendVoice(T chatId, B voice) : BaseMethod("sendVoice") {
            add("chat_id", chatId);
            add("voice", voice);
        }

        [[nodiscard]] SendVoice* caption(const char* caption) {
            add("caption", caption);
            return this;
        }

        // TODO complete enum
        [[nodiscard]] SendVoice* parseMode(Enums::ParseMode parseMode) {
            add("parse_mode", Enums::asString(parseMode));
            return this;
        }

        [[nodiscard]] SendVoice* replyToMessageId(long messageId) {
            add("reply_to_message_id", messageId);
            return this;
        }

        [[nodiscard]] SendVoice* duration(const char* duration) {
            add("duration", duration);
            return this;
        }

    };
}




