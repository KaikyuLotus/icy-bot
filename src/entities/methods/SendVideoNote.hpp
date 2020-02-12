#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/enums/Enums.hpp>
#include <entities/Message.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SendVideoNote : public BaseMethod<BaseResponse<Message>> {
    public:
        template <typename T, typename B, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value && TemplateUtils::is_input_file_or_token<B>::value>>
        SendVideoNote(T chatId, B videoNote) : BaseMethod("sendVideoNote") {
            add("chat_id", chatId);
            add("video_note", videoNote);
        }

        [[nodiscard]] SendVideoNote* duration(int duration) {
            add("duration", duration);
            return this;
        }

        [[nodiscard]] SendVideoNote* length(int length) {
            add("length", length);
            return this;
        }

        [[nodiscard]] SendVideoNote* replyToMessageId(long messageId) {
            add("reply_to_message_id", messageId);
            return this;
        }

        [[nodiscard]] SendVideoNote* thumb(const char* thumb) {
            add("thumb", thumb);
            return this;
        }

        // TODO shold be input file
        [[nodiscard]] SendVideoNote* thumb(long long &thumb) {
            throw Errors::NotImplementedException("Thumbs are not implemented yet");
        }

    };
}




