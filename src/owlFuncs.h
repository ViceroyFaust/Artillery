#ifndef OWLFUNCS_H_INCLUDED
#define OWLFUNCS_H_INCLUDED

#include <string>
#include <vector>

// Splits a string based on a delimiter and returns as vector of strings
std::vector<std::string> splitStr(const std::string& str, const std::string& delim);

// Removes whitespace on the left side of a string
std::string leftTrim(const std::string& str);

// Removes whitespace on the right side of the string
std::string rightTrim(const std::string& str);

// Removes whitespace from the both sides of the string
std::string trim(const std::string& str);

#endif // OWLFUNCS_H_INCLUDED
