#pragma once

std::string replaceAll(std::string* str, const std::string& from, const std::string& to);

std::string getDirectory();

std::string lowerCase(std::string string);

bool startsWith(std::string string, std::string substring);

bool endsWith(std::string string, std::string substring);

bool contains(std::string string, std::string substring, bool lower = false);

std::vector<std::string> split(std::string string);

std::string readFile(std::string fileName);

std::vector<std::string> splitByChar(std::string string, std::string splitter);

std::vector<std::string> splitByString(std::string s, std::string delim);

std::string readBytes(std::string fileName);

namespace Log {
	enum colors {
		GREEN = 10,
		RED = 12,
		WHITE = 15,
		LIGHT_BLUE = 11,
		GRAY = 8,
		PURPLE = 13
	};

	void applyCout(std::string text, std::string type, colors color);

	void Debug(std::string text);

	void Info(std::string text);

	void Error(std::string text);

	void Action(std::string text);
}