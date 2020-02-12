#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/enums/Enums.hpp>
#include <entities/Message.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SendVideo : public BaseMethod<BaseResponse<Message>> {
    public:
        template <typename T, typename B, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value && TemplateUtils::is_input_file_or_token<B>::value>>
        SendVideo(T chatId, B video) : BaseMethod("sendVideo") {
            add("chat_id", chatId);
            add("video", video);
        }

        [[nodiscard]] SendVideo* duration(int duration) {
            add("duration", duration);
            return this;
        }

        [[nodiscard]] SendVideo* width(int width) {
            add("width", width);
            return this;
        }

        [[nodiscard]] SendVideo* height(int height) {
            add("height", height);
            return this;
        }

        [[nodiscard]] SendVideo* caption(const char* caption) {
            add("caption", caption);
            return this;
        }

        [[nodiscard]] SendVideo* supportsStreaming(const char* supportsStreaming) {
            add("supports_streaming", supportsStreaming);
            return this;
        }

        [[nodiscard]] SendVideo* parseMode(Enums::ParseMode parseMode) {
            add("parse_mode", Enums::asString(parseMode));
            return this;
        }

        [[nodiscard]] SendVideo* replyToMessageId(long messageId) {
            add("reply_to_message_id", messageId);
            return this;
        }

        [[nodiscard]] SendVideo* thumb(const char* thumb) {
            add("thumb", thumb);
            return this;
        }

        // TODO shold be input file
        [[nodiscard]] SendVideo* thumb(long long &thumb) {
            throw Errors::NotImplementedException("Thumbs are not implemented yet");
        }

    };
}




