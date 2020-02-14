#pragma once

#include <core/Requests.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Chat.hpp>
#include <entities/ChatMember.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class GetChatAdministrators : public BaseMethod<BaseResponse<std::vector<ChatMember>>> {
    public:
        template<typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        explicit GetChatAdministrators(T chatId) : BaseMethod("getChatAdministrators") {
            add("chat_id", chatId);
        }
    };
}
