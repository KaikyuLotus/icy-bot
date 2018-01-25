#include<string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <Windows.h>

#include "Utils.hpp"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

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

std::string readFile(std::string fileName) {
	std::ifstream t(fileName);
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

	return str;
}

namespace Log {

	enum colors {
		GREEN = 10,
		RED = 12,
		WHITE = 15,
		LIGHT_BLUE = 11,
		GRAY = 8,
		PURPLE = 13
	};

	void applyCout(std::string text, std::string type, colors color) {
		SetConsoleTextAttribute(hConsole, WHITE);
		std::cout << "[";
		SetConsoleTextAttribute(hConsole, color);
		std::cout << type;
		SetConsoleTextAttribute(hConsole, WHITE);
		std::cout << "] - " << text << std::endl;
	}

	void Debug(std::string text) {
		applyCout(text, " Debug  ", GREEN);
	}

	void Action(std::string text) {
		applyCout(text, " Action ", PURPLE);
	}

	void Info(std::string text) {
		applyCout(text, " Info   ", LIGHT_BLUE);
	}

	void Error(std::string text) {
		applyCout(text, " Error  ", RED);
	}
}