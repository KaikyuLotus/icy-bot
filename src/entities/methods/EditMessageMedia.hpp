#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>
#include <entities/InputMedia.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class EditMessageMedia : public BaseMethod<BaseResponse<bool>> {
    public:
        template <typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        EditMessageMedia(T chatId, int messageId, const InputMedia *media) : BaseMethod("editMessageMedia") {
            // add("media", media);
            add("message_id", messageId);
            add("chat_id", chatId);
        }

        EditMessageMedia(const char* inlineMessageId, const InputMedia *media) : BaseMethod("editMessageMedia") {
            // add("caption", media);
            add("inline_message_id", inlineMessageId);
        }

        [[nodiscard]] EditMessageMedia* parseMode(Enums::ParseMode parseMode) {
            add("parse_mode", Enums::asString(parseMode));
            return this;
        }
    };
}




