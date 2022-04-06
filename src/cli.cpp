#include <iostream>
#include <string>

#include "cli.h"

/* Prints an input prompt string and then returns a line of input as a string */
std::string getInput() {
    std::string in;
    std::string inputPrompt = "@: ";
    std::cout << inputPrompt;
    std::getline(std::cin, in);
    return in;
}
