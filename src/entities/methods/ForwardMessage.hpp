#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

#undef SendMessage

namespace CppTelegramBots {
    class ForwardMessage : public BaseMethod<BaseResponse<Message>> {
    private:
        void actualCreate(const char* text, const char* fromChatId, const char* messageId) {
            add("text", text);
            add("from_chat_id", fromChatId);
        }
    public:
        ForwardMessage(long long &fromChatId, long long chatId, long messageId) : BaseMethod("forwardMessage") {
            actualCreate(std::to_string(chatId).c_str(), std::to_string(fromChatId).c_str(), std::to_string(messageId).c_str());
        }

        ForwardMessage(const char* fromChatId, const char* chatId, const char* messageId) : BaseMethod("forwardMessage") {
            actualCreate(chatId, fromChatId, messageId);
        }

        ForwardMessage(const char* fromChatId, long long chatId, long messageId) : BaseMethod("forwardMessage") {
            actualCreate(std::to_string(chatId).c_str(), fromChatId, std::to_string(messageId).c_str());
        }

        ForwardMessage(long long fromChatId, const char* chatId, const char* messageId) : BaseMethod("forwardMessage") {
            actualCreate(chatId, std::to_string(fromChatId).c_str(), messageId);
        }
    };
}




