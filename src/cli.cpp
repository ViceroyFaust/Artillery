#include <iostream>
#include <string>
#include <vector>

#include "cli.h"

std::string getInput() {
    std::string in;
    std::string inputPrompt = "@: ";
    std::cout << inputPrompt;
    std::getline(std::cin, in);
    return in;
}
