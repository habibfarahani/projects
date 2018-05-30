#include <stdio.h>

#include "EquationParser.h"
#include "EquationEvaluator.h"




int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Program to evaluate an equation specified in an input text file.\n");
        printf("Usage:\n");
        printf("      eval <input file>\n");
        printf("Where:\n");
        printf("      <input file> is a text file containing a set of equations with following requirements:\n");
        printf("         1.<LHS> = <RHS>\n");
        printf("         2.LHS Is always a variable name\n");
        printf("         3.RHS can be a combination of variable names, operators, and unsigned integers.\n");
        printf("         4.RHS can be a combination of variable names, operators, and unsigned integers.\n");
        printf("         5.In this example only + operator is supported.\n");
        printf("Output:\n");
        printf("         1.Should print the value of each variable in ascending order.\n");
        printf("         2.If a avriable does not have a unique solution it should print the exact content of input file and exit.\n");

    }

    EquationParser eqParser(argv[1]);

    if(true == eqParser.parse(EquationEvaluator::Instance().getEquations()))
    {
        if(true == EquationEvaluator::Instance().evaluate())
        {
            EquationEvaluator::Instance().print();
        }
    }
    else
    {
        eqParser.onError();
    }

    return 0;

}