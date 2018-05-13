#pragma once

#include <vector>
#include <JSON\json.hpp>
#include "Requests.hpp"
#include "ForecastDay.hpp"

class Meteo {
public:
	Meteo() { }

	std::vector<ForecastDay> getForecast(std::string city);
};