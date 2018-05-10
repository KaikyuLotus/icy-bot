#pragma once

#include <exception>

namespace errors {

	struct TokenException : public std::exception {
		std::string token;
		std::string error;

		TokenException(std::string error, std::string token) {
			this->token = token;
			this->error = error;
		}

		const char* what() const throw () {
			return error.c_str();
		};
	};

}