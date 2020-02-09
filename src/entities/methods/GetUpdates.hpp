#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class GetUpdates : public BaseMethod<BaseResponse<std::vector<Update>>> {
    public:
        GetUpdates() : BaseMethod("getUpdates") { }

        [[nodiscard]] GetUpdates offset(long offset) {
            add("offset", offset);
            return *this;
        }

        [[nodiscard]] GetUpdates timeout(long timeout) {
            add("timeout", timeout);
            return *this;
        }
    };
}




