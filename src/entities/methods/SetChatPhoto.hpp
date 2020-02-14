#pragma once

#include <core/Requests.hpp>
#include <entities/BaseResponse.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SetChatPhoto : public BaseMethod<BaseResponse<bool>> {
    public:
        template <typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        SetChatPhoto(T chatId, const InputFile *photo) : BaseMethod("setChatPhoto") {
            add("chat_id", chatId);
            add("photo", photo);
        }
    };
}




