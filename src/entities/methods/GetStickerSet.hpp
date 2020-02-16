#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/StickerSet.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class GetStickerSet : public BaseMethod<BaseResponse<StickerSet>> {
    public:
        GetStickerSet(const char* name) : BaseMethod("getStickerSet") {
            add("name", name);
        }
    };
}




