#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>
#include <entities/ChatPermissions.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class RestrictChatMember : public BaseMethod<BaseResponse<bool>> {
    public:
        template<typename T,
                typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        RestrictChatMember(T chatId,
                int userId,
                ChatPermissions permissions) : BaseMethod("restrictChatMember") {
            add("chat_id", chatId);
            add("user_id", userId);
            add("permissions", permissions.toString().c_str());
        }

        [[nodiscard]] RestrictChatMember *untilDate(long untilDate) {
            add("until_date", untilDate);
            return this;
        }

    };
}




