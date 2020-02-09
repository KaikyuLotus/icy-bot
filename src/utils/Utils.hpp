#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <streambuf>

namespace CppTelegramBots {
    std::string replaceAll(std::string *str, const std::string &from, const std::string &to) {
        size_t start_pos = 0;
        while ((start_pos = str->find(from, start_pos)) != std::string::npos) {
            str->replace(start_pos, from.length(), to);
            start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
        return *str;
    }

    std::string lowerCase(std::string string) {
        std::transform(string.begin(), string.end(), string.begin(), ::tolower);
        return string;
    }

    bool startsWith(const std::string &string, const std::string &substring) {
        return _strnicmp(string.c_str(), substring.c_str(), substring.size()) == 0;
    }

    bool endsWith(std::string string, std::string substring) {
        if (substring.size() > string.size()) return false;
        return std::equal(substring.rbegin(), substring.rend(), string.rbegin());
    }

    bool contains(std::string string, std::string substring, bool lower = false) {
        if (lower) {
            substring = lowerCase(substring);
            string = lowerCase(string);
        }
        return (string.find(substring) != std::string::npos);
    }

    std::vector<std::string> split(const std::string &string) {
        std::string buf; // Have a buffer string
        std::stringstream ss(string); // Insert the string into a stream

        std::vector<std::string> tokens; // Create vector to hold our words

        while (ss >> buf)
            tokens.push_back(buf);

        return tokens;
    }

    std::string readStringFile(const std::string &fileName) {
        Log::Debug("Reading '" + fileName + "' file");
        std::ifstream t(fileName);
        std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        Log::Debug("Done reading file");
        if (str.empty()) {
            throw Errors::FileNotFoundException("File '" + fileName + "' not found");
        }
        return str;
    }

    std::vector<std::string> splitByChar(const std::string &string, const std::string &splitter) {
        std::stringstream sstring(string);
        std::string segment;
        std::vector<std::string> seglist;

        while (std::getline(sstring, segment, splitter.c_str()[0])) {
            seglist.push_back(segment);
        }

        return seglist;
    }

    std::vector<std::string> splitByString(const std::string &s, const std::string &delim) {

        std::vector<std::string> result;

        auto start = 0U;
        auto end = s.find(delim);
        while (end != std::string::npos) {
            result.push_back(s.substr(start, end - start));
            start = end + delim.length();
            end = s.find(delim, start);
        }

        result.push_back(s.substr(start, end));

        return result;
    }

    std::string readFullFile(const std::string &fileName) {
        Log::Debug("Reading '" + fileName + "' file");
        std::string data = std::string((std::istreambuf_iterator<char>(std::ifstream(fileName, std::ios::binary))),
                           (std::istreambuf_iterator<char>()));
        if (data.empty()) {
            throw Errors::FileNotFoundException("File '" + fileName + "' not found");
        }
        Log::Debug("Done reading '" + fileName + "'");
        return data;
    }

    std::string readBytes(const std::string &fileName) {
        Log::Debug("Reading '" + fileName + "' file");
        std::string contents;
        std::ifstream in(fileName, std::ios::binary);
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        if (contents.empty()) {
            throw Errors::FileNotFoundException("File '" + fileName + "' not found");
        }
        Log::Debug("Done reading file!");
        return contents;
    }

    template<typename F>
    auto benchmark(F &foo) {
        auto startTime = std::chrono::steady_clock::now();
        auto value = foo();
        auto end = std::chrono::steady_clock::now();
        auto elaps = std::chrono::duration_cast<std::chrono::nanoseconds>(end - startTime);
        Log::Debug("Lambda executed in " + std::to_string(elaps.count()) + " ns");
        return value;
    }
}