#pragma once

#include <string>
#include <JSON/json.hpp>
#include "ForecastDay.hpp"
#include "Requests.hpp"

using json = nlohmann::json;

class Meteo {
public:
	Meteo() {

	}

	std::vector<ForecastDay>getForecast(std::string city) {
		std::string query = "select * from weather.forecast where woeid in (select woeid from geo.places(1) where text=\"" + city + ", IT\") and u='c'";

		json meteo = Requests("https://query.yahooapis.com/v1/public")
			.setMethod("yql")
			.add("q", query)
			.add("format", "json")
			.add("store", "store://datatables.org/alltableswithkeys")
			.fire()
			.getResult()
			.asJson();

		json::array_t forecast = meteo["query"].get<json>()
			["results"].get<json>()
			["channel"].get<json>()
			["item"].get<json>()
			["forecast"].get<json::array_t>();

		std::vector<ForecastDay> result;

		for (unsigned int i = 0; i < forecast.size(); i++) {
			result.push_back(ForecastDay(forecast[i].get<json>()));	
		}
		
		return result;
	}
};