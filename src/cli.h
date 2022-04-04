#ifndef CLI_H_INCLUDED
#define CLI_H_INCLUDED

#include <iostream>
#include <string>

std::string getInput();

std::vector<std::string> splitStr(const std::string& str, const std::string& delim);

std::string leftTrim(const std::string& str);

std::string rightTrim(const std::string& str);

std::string trim(const std::string& str);

#endif // CLI_H_INCLUDED
