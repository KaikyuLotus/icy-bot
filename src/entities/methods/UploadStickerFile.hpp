#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>
#include <entities/File.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class UploadStickerFile : public BaseMethod<BaseResponse<File>> {
    public:
        UploadStickerFile(int userId, const InputFile *pngSticker) : BaseMethod("sendSticker") {
            add("user_id", userId);
            add("png_sticker", pngSticker);
        }
    };
}
