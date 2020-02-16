#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class EditMessageText : public BaseMethod<BaseResponse<bool>> {
    public:
        template <typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        EditMessageText(T chatId, int messageId, const char* text) : BaseMethod("editMessageText") {
            add("text", text);
            add("message_id", messageId);
            add("chat_id", chatId);
        }

        EditMessageText(const char* inlineMessageId, const char* text) : BaseMethod("editMessageText") {
            add("text", text);
            add("inline_message_id", inlineMessageId);
        }

        [[nodiscard]] EditMessageText* parseMode(Enums::ParseMode parseMode) {
            add("parse_mode", Enums::asString(parseMode));
            return this;
        }
    };
}




