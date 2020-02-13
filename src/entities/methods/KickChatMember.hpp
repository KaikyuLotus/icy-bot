#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

#undef SendMessage

namespace CppTelegramBots {
    class KickChatMember : public BaseMethod<BaseResponse<bool>> {
    public:
        template <typename T,
            typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        KickChatMember(T chatId, int userId) : BaseMethod("kickChatMember") {
            add("chat_id", chatId);
            add("user_id", userId);
        }

        [[nodiscard]] KickChatMember* untilDate(long untilDate) {
            add("until_date", untilDate);
            return this;
        }

    };
}




