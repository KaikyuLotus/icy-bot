#pragma once

class Result {
	std::string result;

public:
	Result(std::string result) {
		this->result = result;
	}

	std::string asString() {
		return this->result;
	}

	json asJson() {
		return json::parse(result);
	}

	json::array_t asJsonArray(std::string keyName) {
		return json::parse(result)[keyName].get<json::array_t>();
	}
};