#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

#undef SendMessage

namespace CppTelegramBots {
    class SendMessage : public BaseMethod<BaseResponse<Message>> {
    private:
        void actualCreate(const char* text, const char* chatId) {
            add("text", text);
            add("chat_id", chatId);
        }
    public:
        SendMessage(long long chatId, const char* text) : BaseMethod("sendMessage") {
            actualCreate(text, std::to_string(chatId).c_str());
        }

        SendMessage(const char* chatId, const char* text) : BaseMethod("sendMessage") {
            actualCreate(text, chatId);
        }

        [[nodiscard]] SendMessage replyToMessageId(long messageId) {
            add("reply_to_message_id", messageId);
            return *this;
        }

        [[nodiscard]] SendMessage parseMode(Enums::ParseMode parseMode) {
            add("parse_mode", Enums::asString(parseMode).c_str());
            return *this;
        }
    };
}




