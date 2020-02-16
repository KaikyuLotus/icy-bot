#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class EditMessageCaption : public BaseMethod<BaseResponse<bool>> {
    public:
        template <typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        EditMessageCaption(T chatId, int messageId, const char* caption) : BaseMethod("editMessageCaption") {
            add("caption", caption);
            add("message_id", messageId);
            add("chat_id", chatId);
        }

        EditMessageCaption(const char* inlineMessageId, const char* caption) : BaseMethod("editMessageCaption") {
            add("caption", caption);
            add("inline_message_id", inlineMessageId);
        }

        [[nodiscard]] EditMessageCaption* parseMode(Enums::ParseMode parseMode) {
            add("parse_mode", Enums::asString(parseMode));
            return this;
        }
    };
}




