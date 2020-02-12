#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

#undef SendMessage

namespace CppTelegramBots {
    class StopMessageLiveLocation : public BaseMethod<BaseResponse<Message>> {
    public:
        template <typename T,
            typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        StopMessageLiveLocation(T chatId, int messageId) : BaseMethod("stopMessageLiveLocation") {
            add("chat_id", chatId);
            add("message_id", messageId);
        }

        explicit StopMessageLiveLocation(const char* inlineMessageId) : BaseMethod("stopMessageLiveLocation") {
            add("inline_message_id", inlineMessageId);
        }
    };
}




