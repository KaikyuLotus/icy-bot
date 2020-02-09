#pragma once

#include <json.hpp>

namespace CppTelegramBots {
    template<typename T>
    class BaseResponse {
    public:
        bool ok{};
        int errorCode{};
        std::string description{};
        T result;

        bool hasErrorCode = false;
        bool hasDescription = false;
        bool hasResult = false;
    };

    template<typename T>
    void from_json(const nlohmann::json& json, BaseResponse<T>& baseResponse) {
        json.at("ok").get_to(baseResponse.ok);

        if (json.count("error_code") != 0) {
            json.at("error_code").get_to(baseResponse.errorCode);
            baseResponse.hasErrorCode = true;
        }
        if (json.count("description") != 0) {
            json.at("description").get_to(baseResponse.description);
            baseResponse.hasDescription = true;
        }
        if (json.count("result") != 0) {
            json.at("result").get_to(baseResponse.result);
            baseResponse.hasResult = true;
        }
    }
}





