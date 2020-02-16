#pragma once

#include <entities/BaseResponse.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class DeleteMessage : public BaseMethod<BaseResponse<bool>> {
    public:
        template <typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        DeleteMessage(T chatId, int messageId) : BaseMethod("deleteMessage") {
            add("message_id", messageId);
            add("chat_id", chatId);
        }
    };
}
