#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

#undef SendMessage

namespace CppTelegramBots {
    class SendLocation : public BaseMethod<BaseResponse<Message>> {
    public:
        template <typename T,
            typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        SendLocation(T chatId, float latitude, float longitude) : BaseMethod("sendLocation") {
            add("chat_id", chatId);
            add("latitude", latitude);
            add("longitude", longitude);
        }

        [[nodiscard]] SendLocation* livePeriod(int livePeriod) {
            add("live_period", livePeriod);
            return this;
        }

        [[nodiscard]] SendLocation* replyToMessageId(long messageId) {
            add("reply_to_message_id", messageId);
            return this;
        }
    };
}




