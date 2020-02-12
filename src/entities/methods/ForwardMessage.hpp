#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

#undef SendMessage

namespace CppTelegramBots {
    class ForwardMessage : public BaseMethod<BaseResponse<Message>> {
    public:
        template <typename T, typename B,
                typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value
                        && TemplateUtils::is_valid_chat_id<B>::value>>
        ForwardMessage(T toChatId, B fromChatId, int messageId) : BaseMethod("forwardMessage") {
            add("chat_id", toChatId);
            add("from_chat_id", fromChatId);
            add("message_id", messageId);
        }
    };
}




