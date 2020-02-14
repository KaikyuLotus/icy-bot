#pragma once

#include <core/Requests.hpp>
#include <entities/BaseResponse.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class LeaveChat : public BaseMethod<BaseResponse<bool>> {
    public:
        template <typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        explicit LeaveChat(T chatId) : BaseMethod("leaveChat") {
            add("chat_id", chatId);
        }
    };
}
