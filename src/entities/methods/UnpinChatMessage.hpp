#pragma once

#include <core/Requests.hpp>
#include <entities/BaseResponse.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class UnpinChatMessage : public BaseMethod<BaseResponse<bool>> {
    public:
        template <typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        explicit UnpinChatMessage(T chatId) : BaseMethod("unpinChatMessage") {
            add("chat_id", chatId);
        }
    };
}
