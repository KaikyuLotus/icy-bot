#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

#undef SendMessage

namespace CppTelegramBots {
    class EditMessageLiveLocation : public BaseMethod<BaseResponse<Message>> {
    public:
        template <typename T,
            typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        EditMessageLiveLocation(T chatId, int messageId, float latitude, float longitude) : BaseMethod("editMessageLiveLocation") {
            add("chat_id", chatId);
            add("message_id", messageId);
            add("latitude", latitude);
            add("longitude", longitude);
        }

        explicit EditMessageLiveLocation(const char* inlineMessageId, float latitude, float longitude) : BaseMethod("editMessageLiveLocation") {
            add("inline_message_id", inlineMessageId);
            add("latitude", latitude);
            add("longitude", longitude);
        }
    };
}




