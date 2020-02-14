#pragma once

#include <core/Requests.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Chat.hpp>
#include <entities/ChatMember.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SetChatStickerSet : public BaseMethod<BaseResponse<bool>> {
    public:
        template<typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        explicit SetChatStickerSet(T chatId, const char *stickerSetName) : BaseMethod("setChatStickerSet") {
            add("chat_id", chatId);
            add("sticker_set_name", stickerSetName);
        }
    };
}