#pragma once

#include <entities/BaseResponse.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class DeleteStickerFromSet : public BaseMethod<BaseResponse<bool>> {
    public:
        explicit DeleteStickerFromSet(const char *sticker) : BaseMethod(
                "deleteStickerFromSet") {
            add("sticker", sticker);
        }
    };
}
