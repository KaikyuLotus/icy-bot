#pragma once
#include <CURL/curl.h> 
#include <fstream>
#include "Result.hpp"

class MethodsManager {
	CURL* curl;
	CURLcode res;

	int nArgs;

	std::string readBuffer;
	std::string baseUrl{ "https://api.telegram.org/bot" };
	std::string token;
	std::string args;
	std::string fileType;
	std::string fileName;
	std::string method;
	std::string contents;

	bool isPost{ false };

	static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
	{
		((std::string*)userp)->append((char*)contents, size * nmemb);
		return size * nmemb;
	}

	void cleanUp() {
		isPost = false;
		curl = 0;
		args = "";
		nArgs = 0;
		readBuffer = std::string();
	}

	MethodsManager fireGet() {
		this->curl = curl_easy_init();
		if (!this->curl) {
			std::cout << "Critical error in MethodManager." << std::endl;
			throw EXCEPTION_ACCESS_VIOLATION;
		}

		std::string tmpUrl{ baseUrl + token + "/" + method + args };

		curl_easy_setopt(curl, CURLOPT_URL, tmpUrl.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);
		if (res != 0) {
			if (res == 3) {
				Log::Error("Malformed URL: " + tmpUrl);
			} else {
				Log::Error("Curl returned: " + std::to_string(res));
				Log::Error("Request response: " + readBuffer);
			}
		}

		curl_easy_cleanup(curl);
		return *this;

	}

	MethodsManager firePost() {
		this->curl = curl_easy_init();
		if (!this->curl) {
			std::cout << "Critical error in MethodManager." << std::endl;
			throw EXCEPTION_ACCESS_VIOLATION;
		}

		std::string tmpUrl{ baseUrl + token + "/" + method + args };

		struct curl_httppost *formpost = NULL;
		struct curl_httppost *lastptr = NULL;
		struct curl_slist *headerlist = NULL;
		static const char buf[] = "Expect:";

		curl_global_init(CURL_GLOBAL_ALL);

		// set up the header
		curl_formadd(&formpost,
			&lastptr,
			CURLFORM_COPYNAME, "cache-control:",
			CURLFORM_COPYCONTENTS, "no-cache",
			CURLFORM_END);

		curl_formadd(&formpost,
			&lastptr,
			CURLFORM_COPYNAME, "cache-control:",
			CURLFORM_COPYCONTENTS, "no-cache",
			CURLFORM_END);

		curl_formadd(&formpost,
			&lastptr,
			CURLFORM_COPYNAME, "content-type:",
			CURLFORM_COPYCONTENTS, "multipart/form-data",
			CURLFORM_END);

		curl_formadd(&formpost, &lastptr,
			CURLFORM_COPYNAME, fileType.c_str(),
			CURLFORM_BUFFER, fileName.c_str(),
			CURLFORM_BUFFERPTR, contents.data(),
			CURLFORM_BUFFERLENGTH, contents.size(),
			CURLFORM_END);

		headerlist = curl_slist_append(headerlist, buf);

		curl_easy_setopt(curl, CURLOPT_URL, tmpUrl.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);
		if (res != 0)
			Log::Debug("Invalid curl result: " + std::to_string(res));

		curl_easy_cleanup(curl);
		curl_formfree(formpost);
		curl_slist_free_all(headerlist);

		contents = "";

		return *this;
	}

public:
	MethodsManager(std::string token) {
		this->token = token;
	}

	// Setting the method means resetting the request
	MethodsManager setMethod(std::string method) {
		this->method = method;
		cleanUp();
		return *this;
	}

	Result getResult() {
		return Result(readBuffer);
	}

	MethodsManager add(std::string name, std::string value) {
		args += ((nArgs == 0) ? "?" : "&") + name + "=" + curl_easy_escape(curl, value.c_str(), value.size());
		nArgs++;
		return *this;
	}

	MethodsManager add(std::string name, int value) {
		return add(name, std::to_string(value));
	}

	MethodsManager add(std::string name, long long value) {
		return add(name, std::to_string(value));
	}

	MethodsManager add(std::string name, std::string fileName, std::string contents) {
		this->fileType = name;
		this->fileName = fileName;
		this->isPost = true;
		this->contents = contents;

		return *this;
	}

	MethodsManager fire() {
		if (isPost) return firePost();
		else return fireGet();
	}

	
};