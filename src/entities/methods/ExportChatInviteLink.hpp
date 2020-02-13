#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class ExportChatInviteLink : public BaseMethod<BaseResponse<std::string>> {
    public:
        template<typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        explicit ExportChatInviteLink(T chatId) : BaseMethod("exportChatInviteLink") {
            add("chat_id", chatId);
        }
    };
}




