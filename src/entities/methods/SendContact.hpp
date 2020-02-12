#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

#undef SendMessage

namespace CppTelegramBots {
    class SendContact : public BaseMethod<BaseResponse<Message>> {
    public:
        template <typename T,
            typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        SendContact(T chatId, const char* phoneNumber, const char* firstName) : BaseMethod("sendVenue") {
            add("chat_id", chatId);
            add("phone_number", phoneNumber);
            add("first_name", firstName);
        }

        [[nodiscard]] SendContact* last_name(const char* lastName) {
            add("last_name", lastName);
            return this;
        }

        [[nodiscard]] SendContact* vcard(const char* vcard) {
            add("vcard", vcard);
            return this;
        }

        [[nodiscard]] SendContact* replyToMessageId(long messageId) {
            add("reply_to_message_id", messageId);
            return this;
        }
    };
}




