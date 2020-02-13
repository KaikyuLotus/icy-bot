#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>
#include <entities/UserProfilePhotos.hpp>

#include "BaseMethod.hpp"

#undef SendMessage

namespace CppTelegramBots {
    class GetUserProfilePhotos : public BaseMethod<BaseResponse<UserProfilePhotos>> {
    public:
        explicit GetUserProfilePhotos(int userId) : BaseMethod("getUserProfilePhotos") {
            add("user_id", userId);
        }

        [[nodiscard]] GetUserProfilePhotos* offset(int offset) {
            add("offset", offset);
            return this;
        }

        [[nodiscard]] GetUserProfilePhotos* limit(int limit) {
            add("limit", limit);
            return this;
        }
    };
}




