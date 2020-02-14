#pragma once

#include <core/Requests.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Chat.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class GetChat : public BaseMethod<BaseResponse<Chat>> {
    public:
        template <typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        explicit GetChat(T chatId) : BaseMethod("getChat") {
            add("chat_id", chatId);
        }
    };
}
