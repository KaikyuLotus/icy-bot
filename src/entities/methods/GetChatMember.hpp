#pragma once

#include <core/Requests.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Chat.hpp>
#include <entities/ChatMember.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class GetChatMember : public BaseMethod<BaseResponse<ChatMember>> {
    public:
        template<typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        explicit GetChatMember(T chatId, int userId) : BaseMethod("getChatMember") {
            add("chat_id", chatId);
            add("user_id", userId);
        }
    };
}