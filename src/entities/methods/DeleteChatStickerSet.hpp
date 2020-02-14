#pragma once

#include <core/Requests.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Chat.hpp>
#include <entities/ChatMember.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class DeleteChatStickerSet : public BaseMethod<BaseResponse<bool>> {
    public:
        template<typename T, typename = std::enable_if_t<TemplateUtils::is_valid_chat_id<T>::value>>
        explicit DeleteChatStickerSet(T chatId) : BaseMethod("deleteChatStickerSet") {
            add("chat_id", chatId);
        }
    };
}