#pragma once

#include <core/Requests.hpp>
#include <entities/BaseResponse.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SetChatTitle : public BaseMethod<BaseResponse<bool>> {
    public:
        template <typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        explicit SetChatTitle(T chatId, const char *title) : BaseMethod("setChatTitle") {
            add("chat_id", chatId);
            add("title", title);
        }
    };
}
