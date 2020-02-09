#pragma once

#include <string>
#include <iostream>
#include <cpprest/http_client.h>

#include "utils/Log.hpp"
#include "utils/Errors.hpp"
#include "utils/Utils.hpp"
#include "core/RequestResult.hpp"
#include "entities/methods/BaseMethod.hpp"

using namespace web::http;

namespace CppTelegramBots {

    struct RequestsUtils {

        static std::string genBoundary() {
            std::string boundary{};
            for (int i = 0; i < 50; i++) {
                boundary += (rand() % 26) + 'A';
            }
            return boundary;
        }

        static std::pair<std::string, std::string> generateFormData(const InputFile &inputFile) {
            std::string boundary = genBoundary();
            std::stringstream data;
            data << "--" << boundary << "\r\n"
                 << "Content-Disposition: form-data; name=\"photo\"; filename=\""
                 << inputFile.name << "\"\r\nContent-Type: application/octet-stream\r\n\r\n"
                 << inputFile.content << "\r\n\r\n"
                 << "--" << boundary << "--";

            return { boundary, data.str() };
        }

        static utility::string_t endpoint(const char* endpointString, const char* token) {
            return utility::conversions::to_string_t("/bot" + std::string(token) + "/" + endpointString);
        }

        template <class T>
        static client::http_client getClient(const BaseMethod<T> &base_m, const char* token) {
            utility::string_t pathUrl = base_m.getUriBuilder().set_path(endpoint(base_m.endpoint.c_str(), token)).to_string();
            utility::string_t fullUrl = utility::conversions::to_string_t(baseUrl) + pathUrl;
            client::http_client_config client_config = client::http_client_config();
            client_config.set_timeout(std::chrono::seconds(120));
            return client::http_client(fullUrl, client_config);
        }

        static http_request generateRequest(const std::vector<InputFile> &inputFiles) {
            if (inputFiles.size() > 1) {
                throw Errors::NotImplementedException("Multiple post files not implemented yet");
            }

            Log::Debug("Generating request");
            http_request msg{};
            if (!inputFiles.empty()) {
                msg = http_request{ methods::POST };
                auto p = generateFormData(inputFiles.at(0));
                msg.set_body(p.second, "multipart/form-data; boundary=" + p.first);
            } else {
                msg = http_request{ methods::GET };
            }

            return msg;
        }

        static std::string asStdString(const utility::string_t &stringt) {
            return utility::conversions::to_utf8string(stringt);
        }
    };

    class Requests {
    private:

        template <class T>
        RequestResult<T> _fire(const BaseMethod<T> &base_m, const char* token) {
            http_request request = RequestsUtils::generateRequest(base_m.inputFiles);
            Log::Debug("Sending request");
            utility::string_t s = benchmark([&]() {
                return RequestsUtils::getClient(base_m, token)
                    .request(request).get()
                    .extract_string().get();
            });
            return RequestResult<T>(RequestsUtils::asStdString(s));
        }

    public:
        Requests() = default;

        template <class T>
        RequestResult<T> fire(const BaseMethod<T> &base_request, const char* token) {
            return RequestResult<T>(_fire(base_request, token));
        }

    };
}
