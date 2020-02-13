#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>
#include <entities/ChatPermissions.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SetChatPermissions : public BaseMethod<BaseResponse<bool>> {
    public:
        template<typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        SetChatPermissions(T chatId, ChatPermissions permissions) : BaseMethod("setChatPermissions") {
            add("chat_id", chatId);
            add("permissions", permissions.toString().c_str());
        }
    };
}
