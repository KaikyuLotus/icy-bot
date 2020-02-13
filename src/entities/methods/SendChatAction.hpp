#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

#undef SendMessage

namespace CppTelegramBots {
    class SendChatAction : public BaseMethod<BaseResponse<bool>> {
    public:
        template <typename T,
            typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        SendChatAction(T chatId, Enums::ChatAction action) : BaseMethod("sendChatAction") {
            add("chat_id", chatId);
            add("action", Enums::asString(action));
        }
    };
}




