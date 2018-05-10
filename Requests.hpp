#pragma once

#include <CURL/curl.h> 
#include <fstream>
#include <iostream>
#include <string>
#include "Result.hpp"
#include "Utils.hpp"

class Requests {
private:
	CURL * curl;
	CURLcode res;

	int nArgs;
	bool isPost = false;
	std::string args = "";
	std::string url = "";
	std::string readBuffer;

	static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
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

	Requests fireGet() {
		this->curl = curl_easy_init();
		if (!this->curl) {
			std::cout << "Critical error in MethodManager." << std::endl;
			throw EXCEPTION_ACCESS_VIOLATION;
		}

		std::string tmpUrl{ url + args};

		curl_easy_setopt(curl, CURLOPT_URL, tmpUrl.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);
		if (res != 0) {
			Log::Error("Curl returned: " + std::to_string(res));
			Log::Error("Request response: " + readBuffer);
		}

		curl_easy_cleanup(curl);
		return *this;
	}

public:
	Requests(std::string url) {
		this->url = url;
	}

	// Setting the method means resetting the request
	Requests setMethod(std::string method) {
		this->url += "/" + method;
		cleanUp();
		return *this;
	}

	Result getResult() {
		return Result(readBuffer);
	}

	Requests add(std::string name, std::string value) {
		args += ((nArgs == 0) ? "?" : "&") + name + "=" + curl_easy_escape(curl, value.c_str(), value.size());
		nArgs++;
		return *this;
	}

	Requests add(std::string name, int value) {
		return add(name, std::to_string(value));
	}

	Requests add(std::string name, long long value) {
		return add(name, std::to_string(value));
	}

	// Not implemented yet
	/*Requests add(std::string name, std::string fileName, std::string contents) {
		this->fileType = name;
		this->fileName = fileName;
		this->isPost = true;
		this->contents = contents;

		return *this;
	}*/

	Requests fire() {
		//if (isPost) return firePost();
		//else return
		return fireGet();
	}
};