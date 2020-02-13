#pragma once

#include <core/Requests.hpp>
#include <entities/User.hpp>
#include <entities/BaseResponse.hpp>
#include <entities/Update.hpp>
#include <entities/enums/Enums.hpp>
#include <entities/File.hpp>

#include "BaseMethod.hpp"

#undef SendMessage

namespace CppTelegramBots {
    class GetFile : public BaseMethod<BaseResponse<File>> {
    public:
        explicit GetFile(const char* fileId) : BaseMethod("getFile") {
            add("file_id", fileId);
        }
    };
}




