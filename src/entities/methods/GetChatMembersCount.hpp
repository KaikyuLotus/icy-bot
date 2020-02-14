#pragma once

#include <core/Requests.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Chat.hpp>
#include <entities/ChatMember.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class GetChatMembersCount : public BaseMethod<BaseResponse<int>> {
    public:
        template<typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        explicit GetChatMembersCount(T chatId) : BaseMethod("getChatMembersCount") {
            add("chat_id", chatId);
        }
    };
}
