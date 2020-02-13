#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"


namespace CppTelegramBots {
    class SetChatAdministratorCustomTitle : public BaseMethod<BaseResponse<bool>> {
    public:
        template<typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        SetChatAdministratorCustomTitle(T chatId, int userId, const char *customTitle) : BaseMethod("setChatAdministratorCustomTitle") {
            add("chat_id", chatId);
            add("user_id", userId);
            add("custom_title", customTitle);
        }
    };
}




