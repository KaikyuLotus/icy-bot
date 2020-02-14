#pragma once

#include <core/Requests.hpp>
#include <entities/BaseResponse.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class DeleteChatPhoto : public BaseMethod<BaseResponse<bool>> {
    public:
        template <typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        explicit DeleteChatPhoto(T chatId) : BaseMethod("deleteChatPhoto") {
            add("chat_id", chatId);
        }
    };
}
