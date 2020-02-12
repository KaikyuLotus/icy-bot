#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/enums/Enums.hpp>
#include <entities/Message.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SendAnimation : public BaseMethod<BaseResponse<Message>> {
    public:
        template <typename T, typename B, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value && TemplateUtils::is_input_file_or_token<B>::value>>
        SendAnimation(T chatId, B animation) : BaseMethod("sendAnimation") {
            add("chat_id", chatId);
            add("animation", animation);
        }

        [[nodiscard]] SendAnimation* duration(int duration) {
            add("duration", duration);
            return this;
        }

        [[nodiscard]] SendAnimation* width(int width) {
            add("width", width);
            return this;
        }

        [[nodiscard]] SendAnimation* height(int height) {
            add("height", height);
            return this;
        }

        [[nodiscard]] SendAnimation* caption(const char* caption) {
            add("caption", caption);
            return this;
        }

        [[nodiscard]] SendAnimation* parseMode(Enums::ParseMode parseMode) {
            add("parse_mode", Enums::asString(parseMode));
            return this;
        }

        [[nodiscard]] SendAnimation* replyToMessageId(long messageId) {
            add("reply_to_message_id", messageId);
            return this;
        }

        [[nodiscard]] SendAnimation* thumb(const char* thumb) {
            add("thumb", thumb);
            return this;
        }

        // TODO shold be input file
        [[nodiscard]] SendAnimation* thumb(long long &thumb) {
            throw Errors::NotImplementedException("Thumbs are not implemented yet");
        }

    };
}




