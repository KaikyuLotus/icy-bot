#include "Meteo.hpp"

std::vector<ForecastDay> Meteo::getForecast(std::string city) {
	std::string query = "select * from weather.forecast where woeid in (select woeid from geo.places(1) where text=\"" + city + ", IT\") and u='c'";

	nlohmann::json meteo = Requests("https://query.yahooapis.com/v1/public")
		.setMethod("yql")
		.add("q", query)
		.add("format", "json")
		.add("store", "store://datatables.org/alltableswithkeys")
		.fire()
		.getResult()
		.asJson();

	nlohmann::json::array_t forecast = meteo["query"].get<nlohmann::json>()
		["results"].get<nlohmann::json>()
		["channel"].get<nlohmann::json>()
		["item"].get<nlohmann::json>()
		["forecast"].get<nlohmann::json::array_t>();

	std::vector<ForecastDay> result;

	for (unsigned int i = 0; i < forecast.size(); i++) {
		result.push_back(ForecastDay(forecast[i].get<nlohmann::json>()));
	}

	return result;
}