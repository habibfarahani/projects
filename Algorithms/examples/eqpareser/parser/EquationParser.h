#ifndef __EQ_PARSER__
#define __EQ_PARSER__


#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "Equation.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///  @brief: 
///     Equation parser class is used to:
///         1. Take an input file name.
///         2. Parse the file line by line.
///         3. Split each line into an array of strings comprised of Veriables, 
///             and operators (only addition for now), and constant literals (only unsigned int for now)
///         4. For each line an Equation object will be contructed and each parameter (variables or conatants)
///             and each operator will be added to the equation object.
///         5. Each equation object will contain a VECTOR of operators and a VECTOR of parameters.
///         6. In the end each equation object then is inserted into a MAP of equations where the LHS will be the 
///             key element of the MAP.
///         7.  Once all Equations are inserted in the MAP, the routine verifies that:
///                 a.  There are no unresolved externals.  Which means that all variables have a UNIQUE solution.
///                 b.  There are circular dependency between variables as it needs algenraic methods to solve
///                     solve such dependecies.  This capability can be added with current architecture.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EquationParser
{
    public:
    EquationParser(const std::string &streamName)
    {
        m_sName = streamName;
    }
    ~EquationParser(){}

    //////////////////////////////////////////////////////////////////////////////////////
    ///  @brief: 
    ///     Public parse method that populates a map of equation from an
    ///     input text file.
    ///     @param eqMap sorted map of equations to be constructed.
    //////////////////////////////////////////////////////////////////////////////////////
    bool parse(EqMap &eqMap);

    std::string & getLastError()
    {
        return m_lastError;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    /// This method should be called when verify fails.
    /// It prints the the error message, if one exists, and then print the entire input
    /// file for the user.
    //////////////////////////////////////////////////////////////////////////////////////
    bool onError();

    protected:
    //////////////////////////////////////////////////////////////////////////////////////
    ///  @brief: 
    ///     Overloaded parse method that take an input string object
    ///     and splits it into substrings seperated by spaces.
    /// @param line: Input string (a line of the file)
    /// @param arr: Array of string formatted as:
    ///     element 0:        LHS (denoting a variable name)
    ///     element 1:        = (Equal sign has to be here for it to be  avalid equation)
    ///     element 2..n:     RHS (Which is comprised of literal values, variables, and operators)
    ///     This corresponds to: LHS = RHS
    /// @return true if succeeded.  Otherwise false.
    ///     In case of a failure the actual error string is available via getLastError()
    //////////////////////////////////////////////////////////////////////////////////////
    bool parse(std::string &line, std::vector<std::string> &arr);

    //////////////////////////////////////////////////////////////////////////////////////
    // This method is used to create an equation object from a array of strings which
    // represents each line in the input file.
    // For example:  {"Var1", "=", "1" + "Var2", "+", "3"}
    //////////////////////////////////////////////////////////////////////////////////////
    bool createEquation(std::vector<std::string> &arr, EqMap &eqMap);

    //////////////////////////////////////////////////////////////////////////////////////
    // Method to verify the entire MAP of the equation after they all equations are:
    //      1. Verfied.
    //      2. successfully inserted in the MAP
    // It will:
    //  1. Makes sure there are no unrefereced variables.
    //  2. Makes sure there are no circular variable dependecies
    //      For example:
    //          Var1 = 3 + Var2 + 8
    //          Var2 = Var1 + 6
    //  Though the above example is valid in algenraic terms.  No support for Algebraic
    //  equation solving is proposed here. Though propsed model can be extended to add this support.
    //////////////////////////////////////////////////////////////////////////////////////
    bool verify(EqMap &eqMap);

    private:
    std::string m_sName;            // Name associated with this equation(only for tracking purposes)
    std::string m_lastError;        // The last logged error string

    bool insert(Equation *eq, std::string name, EqMap &eqMap);


    //////////////////////////////////////////////////////////////////////////////////////
    /// These method used to scan the set of equations to detect any unresolved refernce to a
    /// variable or any type of circular dependency.  The latter means if the dependency
    /// tree of a variable comes back to itself.
    /// To support this type of equation we need to have a algebraic algorithm.
    //////////////////////////////////////////////////////////////////////////////////////
   
    bool checkUnresolvedRef(std::string name, EqMap &eqMap);
    bool circularIndep(std::vector<std::string> &depArr, EqMap &eqMap);
    bool circularIndep(std::vector<std::string> &depArr, Equation *pEq, EqMap &eqMap);
    bool findDuplicate(std::string element, std::vector<std::string> &depArr);
    
};

#endif  //  __EQ_PARSER__
