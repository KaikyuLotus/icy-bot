#pragma once

#include <entities/BaseResponse.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class EditMessageReplyMarkup : public BaseMethod<BaseResponse<bool>> {
    public:
        template <typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        EditMessageReplyMarkup(T chatId, int messageId) : BaseMethod("editMessageReplyMarkup") {
            add("message_id", messageId);
            add("chat_id", chatId);
        }

        explicit EditMessageReplyMarkup(const char* inlineMessageId) : BaseMethod("editMessageReplyMarkup") {
            add("inline_message_id", inlineMessageId);
        }
    };
}
