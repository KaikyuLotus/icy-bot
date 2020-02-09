#pragma once

#include <exception>
#include <string>

namespace CppTelegramBots::Errors {

    struct TokenException : public std::exception {
        std::string token;
        std::string error;

        TokenException(const std::string& error, const std::string& token) {
            this->token = token;
            this->error = error;
        }

        [[nodiscard]] const char *what() const noexcept override {
            return error.c_str();
        };
    };

    struct ExecutorException : public std::exception {
        std::string error;

        explicit ExecutorException(const std::string& error) {
            this->error = error;
        }

        [[nodiscard]] const char *what() const noexcept override {
            return error.c_str();
        };
    };

    struct FileNotFoundException : public std::exception {
        std::string error;

        explicit FileNotFoundException(const std::string& error) {
            this->error = error;
        }

        [[nodiscard]] const char *what() const noexcept override {
            return error.c_str();
        };
    };

    struct NotImplementedException : public std::exception {
        std::string error;

        explicit NotImplementedException(const std::string& error) {
            this->error = error;
        }

        [[nodiscard]] const char *what() const noexcept override {
            return error.c_str();
        };
    };

    struct RequestsException : public std::exception {
        long code;
        std::string url;
        std::string result;
        std::string message;

        RequestsException(const std::string& message, const std::string& url, const std::string& result, long code) {
            this->url = url;
            this->code = code;
            this->result = result;
            this->message = message;
        }

        [[nodiscard]] const char *what() const noexcept override {
            return this->message.c_str();
        };
    };

}