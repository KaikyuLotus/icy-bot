#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

#undef SendMessage

namespace CppTelegramBots {
    class SendPoll : public BaseMethod<BaseResponse<Message>> {
    public:
        template <typename T,
            typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        SendPoll(T chatId, const char* question, std::vector<const char*> options) : BaseMethod("sendPoll") {
            add("chat_id", chatId);
            add("question", question);
            add("options", options);
        }

        [[nodiscard]] SendPoll* isAnonymous(bool isAnonymous) {
            add("is_anonymous", isAnonymous);
            return this;
        }

        [[nodiscard]] SendPoll* type(const char* type) {
            add("type", type);
            return this;
        }

        [[nodiscard]] SendPoll* allowsMultipleAnswers(bool allowsMultipleAnswers) {
            add("allows_multiple_answers", allowsMultipleAnswers);
            return this;
        }

        [[nodiscard]] SendPoll* correctOptionId(int correctOptionId) {
            add("correct_option_id", correctOptionId);
            return this;
        }

        [[nodiscard]] SendPoll* isClosed(bool isClosed) {
            add("is_closed", isClosed);
            return this;
        }

        [[nodiscard]] SendPoll* replyToMessageId(long messageId) {
            add("reply_to_message_id", messageId);
            return this;
        }
    };
}




