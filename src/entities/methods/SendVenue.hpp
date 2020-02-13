#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SendVenue : public BaseMethod<BaseResponse<Message>> {
    public:
        template <typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        SendVenue(T chatId, float latitude, float longitude, const char* title, const char* address) : BaseMethod("sendVenue") {
            add("chat_id", chatId);
            add("latitude", latitude);
            add("longitude", longitude);
            add("title", title);
            add("address", address);
        }

        [[nodiscard]] SendVenue* foursquareId(const char* foursquareId) {
            add("foursquare_id", foursquareId);
            return this;
        }

        [[nodiscard]] SendVenue* foursquareType(const char* foursquareType) {
            add("foursquare_type", foursquareType);
            return this;
        }

        [[nodiscard]] SendVenue* replyToMessageId(long messageId) {
            add("reply_to_message_id", messageId);
            return this;
        }
    };
}
