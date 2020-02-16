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
    class AddStickerToSet : public BaseMethod<BaseResponse<bool>> {
    public:
        template<typename T, typename = std::enable_if_t<TemplateUtils::is_input_file_or_token<T>::value>>
        AddStickerToSet(int userId, const char *name, const char *emojis, T pngSticker) : BaseMethod(
                "addStickerToSet") {
            add("user_id", userId);
            add("name", name);
            add("emojis", emojis);
            add("png_sticker", pngSticker);
        }

        [[nodiscard]] AddStickerToSet *maskPosition(const MaskPosition *maskPosition) {
            add("mask_position", maskPosition);
            return this;
        }
    };
}
