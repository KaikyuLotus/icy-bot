#pragma once

#include <json.hpp>
#include <utility>

namespace CppTelegramBots {
    template <class T>
    class RequestResult {
        std::string result;

    public:
        explicit RequestResult(const std::string& result) {
            this->result = result;
        }

        std::string asString() {
            return this->result;
        }

        T as_json() {
            try {
                return nlohmann::json::parse(result).get<T>();
            } catch (nlohmann::detail::parse_error &error) {
                Log::Error("Parse exception: " + std::string(error.what()));
                Log::Error("Cannot parse value: " + result);
                throw error;
            }
        }
    };
}