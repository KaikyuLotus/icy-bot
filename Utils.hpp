#pragma once

std::string lowerCase(std::string string);

bool startsWith(std::string string, std::string substring);

bool contains(std::string string, std::string substring, bool lower = false);

std::vector<std::string> split(std::string string);

std::string readFile(std::string fileName);

std::vector<std::string> splitByChar(std::string string, std::string splitter);

std::vector<std::string> splitByString(std::string s, std::string delim);

namespace Log {
	enum colors;

	void applyCout(std::string text, std::string type, colors color);

	void Debug(std::string text);

	void Info(std::string text);

	void Error(std::string text);

	void Action(std::string text);
}