#pragma once

#include <string>
#include <core/Requests.hpp>
#include <entities/InputFile.hpp>
#include <cpprest/http_client.h>

namespace CppTelegramBots {

    static const char* baseUrl{"https://api.telegram.org"};

    template <typename T>
    class BaseMethod {

        friend class Requests;
        friend class Bot;
        friend struct RequestsUtils;

    protected:

        std::string endpoint{};
        web::http::uri_builder uriBuilder = web::http::uri_builder();
        std::vector<InputFile> inputFiles = {};

        explicit BaseMethod(std::string endpoint) {
            this->endpoint = endpoint;
        }

        [[nodiscard]] web::http::uri_builder getUriBuilder() const {
            return this->uriBuilder;
        }

        BaseMethod add(const char* name, const char* value) {
            uriBuilder.append_query(utility::conversions::to_string_t(name), value);
            return *this;
        }

        BaseMethod add(const char* name, long long value) {
            return add(name, std::to_string(value).c_str());
        }

        BaseMethod add(const char* name, const InputFile &file) {
            inputFiles.push_back(file);
            return *this;
        }

    public:
        [[nodiscard]] BaseMethod disableWebPagePreview() {
            add("disable_web_page_preview", "true");
            return *this;
        }

        [[nodiscard]] BaseMethod disableNotification() {
            add("disable_notification", "true");
            return *this;
        }

        [[nodiscard]] BaseMethod replyMarkup() {
            throw Errors::NotImplementedException("Reply markup not implemented yet");
//            add("reply_markup", ".");
//            return *this;
        }

    };
}


