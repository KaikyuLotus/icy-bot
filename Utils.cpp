#include<string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

#include "Utils.hpp"


bool contains(std::string string, std::string substring, bool lower) {
	if (lower) {
		substring = lowerCase(substring);
		string = lowerCase(string);
	}
	return (string.find(substring) != std::string::npos);
}

bool startsWith(std::string string, std::string substring) {
	if (_strnicmp(string.c_str(), substring.c_str(), substring.size()) == 0) return true;
	return false;
}

std::string lowerCase(std::string string) {
	std::transform(string.begin(), string.end(), string.begin(), ::tolower);
	return string;
}

std::vector<std::string> split(std::string string) {
	std::string buf; // Have a buffer string
	std::stringstream ss(string); // Insert the string into a stream

	std::vector<std::string> tokens; // Create vector to hold our words

	while (ss >> buf)
		tokens.push_back(buf);

	return tokens;
}