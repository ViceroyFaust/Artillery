#ifndef OWLFUNCS_H_INCLUDED
#define OWLFUNCS_H_INCLUDED

#include <string>
#include <vector>

std::vector<std::string> splitStr(const std::string& str, const std::string& delim);

std::string leftTrim(const std::string& str);

std::string rightTrim(const std::string& str);

std::string trim(const std::string& str);

#endif // OWLFUNCS_H_INCLUDED
