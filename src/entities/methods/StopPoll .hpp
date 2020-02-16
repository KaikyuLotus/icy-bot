#pragma once

#include <entities/BaseResponse.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class StopPoll : public BaseMethod<BaseResponse<bool>> {
    public:
        template <typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        StopPoll(T chatId, int messageId) : BaseMethod("editMessageReplyMarkup") {
            add("message_id", messageId);
            add("chat_id", chatId);
        }
    };
}
