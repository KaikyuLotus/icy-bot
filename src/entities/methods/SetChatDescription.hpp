#pragma once

#include <core/Requests.hpp>
#include <entities/BaseResponse.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SetChatDescription : public BaseMethod<BaseResponse<bool>> {
    public:
        template <typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        explicit SetChatDescription(T chatId, const char *description) : BaseMethod("setChatDescription") {
            add("chat_id", chatId);
            add("description", description);
        }
    };
}
