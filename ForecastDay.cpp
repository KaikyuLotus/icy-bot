#include "ForecastDay.hpp"

ForecastDay::ForecastDay(nlohmann::json day) {
	condition = day["text"].get<std::string>();
	high = day["high"].get<std::string>();
	low = day["low"].get<std::string>();
}