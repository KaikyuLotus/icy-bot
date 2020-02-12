#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/enums/Enums.hpp>
#include <entities/Message.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SendAudio : public BaseMethod<BaseResponse<Message>> {
    public:
        template <typename T, typename B, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value && TemplateUtils::is_input_file_or_token<B>::value>>
        SendAudio(T chatId, B audio) : BaseMethod("sendAudio") {
            add("chat_id", chatId);
            add("audio", audio);
        }

        [[nodiscard]] SendAudio* caption(const char* caption) {
            add("caption", caption);
            return this;
        }

        // TODO complete enum
        [[nodiscard]] SendAudio* parseMode(Enums::ParseMode parseMode) {
            add("parse_mode", Enums::asString(parseMode));
            return this;
        }

        [[nodiscard]] SendAudio* replyToMessageId(long messageId) {
            add("reply_to_message_id", messageId);
            return this;
        }
        [[nodiscard]] SendAudio* duration(const char* duration) {
            add("duration", duration);
            return this;
        }

        [[nodiscard]] SendAudio* performer(const char* performer) {
            add("performer", performer);
            return this;
        }

        [[nodiscard]] SendAudio* title(const char* title) {
            add("title", title);
            return this;
        }

        [[nodiscard]] SendAudio* thumb(const char* thumb) {
            add("thumb", thumb);
            return this;
        }

        // TODO shold be input file
        [[nodiscard]] SendAudio* thumb(long long &thumb) {
            throw Errors::NotImplementedException("Thumbs are not implemented yet");
        }

    };
}




