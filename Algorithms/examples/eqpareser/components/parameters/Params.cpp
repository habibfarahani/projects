#include "Params.h"


#include <algorithm> // for std::all_of
#include <cctype>    // for std::isdigit
#include <regex> // for std::regex_match


bool EquationParams::isVariable(const std::string &str)
{
    // using regex to do pattern matching
    return std::regex_match(str, std::regex("^[A-Za-z]+$"));

    // Or using this cool lamda function
    return std::all_of(str.begin(), 
                        str.end(), 
                        [](char c) { return std::isalpha(c); });

    return false;
}


bool EquationParams::isLiteralConst(const std::string &str)
{
    // using regex to do pattern matching
    return std::regex_match(str, std::regex("[+-]?[0-9]+"));

    // Or using this cool lamda function
    return std::all_of(str.begin(), 
                        str.end(), 
                        [](char c) { return std::isdigit(c); });
}

bool EquationParams::isOperator(const std::string &str)
{
    // using regex to do pattern matching
    return std::regex_match(str, std::regex("^[+]+$"));

    return false;
}

bool EquationParams::isEqual(const std::string &str)
{
    if(str == "=")
    {
        return true;
    }
    return false;
}



