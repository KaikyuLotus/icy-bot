#pragma once

#include <core/Requests.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/enums/Enums.hpp>
#include <entities/InputFile.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SendPhoto : public BaseMethod<BaseResponse<Message>> {
    public:
        template <typename T, typename B, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value && TemplateUtils::is_input_file_or_token<B>::value>>
        SendPhoto(T chatId, B photo) : BaseMethod("sendPhoto") {
            add("chat_id", chatId);
            add("photo", photo);
        }

        [[nodiscard]] SendPhoto* caption(const char* caption) {
            add("caption", caption);
            return this;
        }

        // TODO complete enum
        [[nodiscard]] SendPhoto* parseMode(Enums::ParseMode parseMode) {
            add("parse_mode", Enums::asString(parseMode));
            return this;
        }

        [[nodiscard]] SendPhoto* replyToMessageId(long messageId) {
            add("reply_to_message_id", messageId);
            return this;
        }

    };
}




