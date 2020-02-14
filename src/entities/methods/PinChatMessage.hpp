#pragma once

#include <core/Requests.hpp>
#include <entities/BaseResponse.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class PinChatMessage : public BaseMethod<BaseResponse<bool>> {
    public:
        template <typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        explicit PinChatMessage(T chatId, int messageId) : BaseMethod("pinChatMessage") {
            add("chat_id", chatId);
            add("message_id", messageId);
        }
    };
}
