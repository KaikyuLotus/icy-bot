#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SendSticker : public BaseMethod<BaseResponse<Message>> {
    public:
        template <typename T, typename B, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value && TemplateUtils::is_input_file_or_token<B>::value>>
        SendSticker(T chatId, B sticker) : BaseMethod("sendSticker") {
            add("sticker", sticker);
            add("chat_id", chatId);
        }

        [[nodiscard]] SendSticker* replyToMessageId(long messageId) {
            add("reply_to_message_id", messageId);
            return this;
        }
    };
}




