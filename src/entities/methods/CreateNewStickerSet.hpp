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
    class CreateNewStickerSet : public BaseMethod<BaseResponse<bool>> {
    public:
        template<typename T, typename = std::enable_if_t<TemplateUtils::is_input_file_or_token<T>::value>>
        CreateNewStickerSet(int userId, const char *name, const char *title,
                            const char *emojis, T pngSticker, bool containsMasks = false) : BaseMethod(
                "createNewStickerSet") {
            add("user_id", userId);
            add("name", name);
            add("title", title);
            add("emojis", emojis);
            add("png_sticker", pngSticker);
            add("contains_masks", containsMasks);
        }

        [[nodiscard]] CreateNewStickerSet *maskPosition(const MaskPosition *maskPosition) {
            add("mask_position", maskPosition);
            return this;
        }
    };
}
