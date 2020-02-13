#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>
#include <entities/ChatPermissions.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class PromoteChatMember : public BaseMethod<BaseResponse<bool>> {
    public:
        template<typename T,
                typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        PromoteChatMember(T chatId,
                int userId,
                bool canChangeInfo = false,
                bool canPostMessages = false,
                bool canEditMessages = false,
                bool canDeleteMessages = false,
                bool canInviteUsers = false,
                bool canRestrictMembers = false,
                bool canPinMessages = false,
                bool canPromoteMembers = false) : BaseMethod("promoteChatMember") {
            add("chat_id", chatId);
            add("user_id", userId);
            add("can_change_info", canChangeInfo);
            add("can_post_messages", canPostMessages);
            add("can_edit_messages", canEditMessages);
            add("can_delete_messages", canDeleteMessages);
            add("can_invite_users", canInviteUsers);
            add("can_restrict_members", canRestrictMembers);
            add("can_pin_messages", canPinMessages);
            add("can_promote_members", canPromoteMembers);
        }
    };
}




