#pragma once
#include <CURL/curl.h> 
#include <fstream>

class Request {
	std::string readBuffer;
	std::string finalURL;

	int paramsLenght = 0;
	std::string requestParams = "";

	CURL *curl;
	CURLcode res;
	
	static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
	{
		((std::string*)userp)->append((char*)contents, size * nmemb);
		return size * nmemb;
	}

public:
	Request(std::string url) {
		curl = curl_easy_init();
		if (!curl) {
			std::cout << "Critical error in Request()." << std::endl;
			throw EXCEPTION_ACCESS_VIOLATION;
		}
		finalURL = url;
	}

	void addParam(std::string name, std::string value) {
		if (paramsLenght == 0)
			requestParams += "?";
		else
			requestParams += "&";

		requestParams += name + "=" + curl_easy_escape(curl, value.c_str(), value.size());
		paramsLenght++;
	}

	std::string fireRequest()
	{
		finalURL += requestParams;

		curl_easy_setopt(curl, CURLOPT_URL, finalURL.c_str());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);
		if (res != 0) Log::Error("Curl returned: " + std::to_string(res));

		curl_easy_cleanup(curl);

		return readBuffer;
	}

	std::string firePOST(std::string fileName, std::string fileType) {
		struct curl_httppost *formpost = NULL;
		struct curl_httppost *lastptr = NULL;
		struct curl_slist *headerlist = NULL;
		static const char buf[] = "Expect:";

		std::string contents;
		std::ifstream in (fileName, std::ios::binary );

		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();

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

		finalURL += requestParams;
		curl_easy_setopt(curl, CURLOPT_URL, finalURL.c_str());
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

		return readBuffer;
	}
};
