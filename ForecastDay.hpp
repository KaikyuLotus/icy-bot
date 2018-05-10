#pragma once
#include <string>
#include <JSON/json.hpp>

using json = nlohmann::json;

class ForecastDay {
public:
	std::string condition;
	std::string high;
	std::string low;

	ForecastDay(json day) {
		condition = day["text"].get<std::string>();
		high = day["high"].get<std::string>();
		low = day["low"].get<std::string>();
	}
};