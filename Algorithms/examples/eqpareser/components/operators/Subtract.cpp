#include "Subtract.h"

#include <string>

std::string Subtract::evaluate(std::string &lhs, std::string &rhs)
{
    unsigned int num1 = atoi(lhs.c_str());
    unsigned int num2 = atoi(rhs.c_str());


    num1 = num1 - num2;

    std::string res = std::to_string(num1);

    return res;



}
