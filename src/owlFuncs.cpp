#include "owlFuncs.h"

// Splits a string based on a delimiter and returns as vector of strings
std::vector<std::string> splitStr(const std::string& str, const std::string& delim) {
    std::vector<std::string> strings;
    size_t index1 = 0u;
    size_t index2 = str.find(delim, index1);
    while (index2 != std::string::npos) {
        strings.push_back(str.substr(index1, index2 - index1));
        index1 = index2 + 1;
        index2 = str.find(delim, index1);
    }
    strings.push_back(str.substr(index1));
    return strings;
}

// Removes whitespace on the left side of a string
std::string leftTrim(const std::string& str) {
    if (str.empty())
        return str;
    size_t index = 0;
    for (size_t i = 0u; i < str.size(); ++i) {
        if (str[i] != ' ' && str[i] != '\t') {
            index = i;
            break;
        }
    }
    return str.substr(index);
}

// Removes whitespace on the right side of the string
std::string rightTrim(const std::string& str) {
    if (str.empty())
        return str;
    size_t index = 0;
    for (size_t i = str.size() - 1; i > 0; --i) {
        if (str[i] != ' ' && str[i] != '\t') {
            index = i;
            break;
        }
    }
    return str.substr(0, index + 1);
}

// Removes whitespace from the both sides of the string
std::string trim(const std::string& str) {
    return rightTrim(leftTrim(str));
}
