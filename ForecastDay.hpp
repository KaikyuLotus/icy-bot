#pragma once

#include <JSON\json.hpp>

class ForecastDay {
public:
	std::string condition;
	std::string high;
	std::string low;

	ForecastDay(nlohmann::json day);
};