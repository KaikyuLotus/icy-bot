#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>

#include "BaseMethod.hpp"

namespace CppTelegramBots {
    class GetMe : public BaseMethod<BaseResponse<User>> {
    public:
        GetMe() : BaseMethod("getMe") { }
    };
}




