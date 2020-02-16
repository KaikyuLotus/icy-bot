#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>
#include <entities/File.hpp>
#include <entities/MaskPosition.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class SetStickerPositionInSet : public BaseMethod<BaseResponse<bool>> {
    public:
        SetStickerPositionInSet(const char *sticker, int position) : BaseMethod(
                "setStickerPositionInSet") {
            add("position", position);
            add("sticker", sticker);
        }
    };
}
