#ifndef     __EQ_EVALUATOR__
#define     __EQ_EVALUATOR__


#include <map>
#include <string>

#include "Equation.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///  @brief: 
///     Equation Evaluator is a singleton class which is used to;
///         1. Create and maintain the reference to equation MAP.
///         2. Start evaluating each equation and for each variable recurses until a solution is found.
///         3. This routine requires Equation Parser object to have done its part and provided an equation
///             MAP that contains all valid and correct equations.  So the chances that the logic of recusion fails
///             is none unless something is nt accounted for.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EquationEvaluator
{
    public:
    ~EquationEvaluator();

    static EquationEvaluator &Instance();

    EqMap &getEquations()
    {
        return m_equations;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// This is the main evaluation method where the logic uses map to recursively calculate each equation and variable.
    /// The process is as follows:
    ///     1. For each equation in the MAP starting from beginning.
    ///     2. Get the first parameter and if it is a variable, recuse into evaluate.
    ///     3. If the first param is a literal constant the start a loop for the number of operators.
    ///     4. Store the results in the associated Equation object so it well become (Evaluated = true)
    ///     5. Store the evaluated results in currentValue.
    ///     6. For each operator in the Equation get the next param (keep in mind the each equation is already verfied by parser object)
    ///     7. Follow the same steps as step 2 and store the results in newValue.
    ///     8. Now with currentValue and newValue in hand, perform the operation and store the results in currentValue.
    ///     9. Keep repeating steps 6 and on ward for each operator.
    ///     10. Once we are done with the operators, then currentValue holds the value that needs to be assigned to the
    ///         Equation object at hand which is also represented by a variable (its LHS) used a key into its MAP entry.
    ///     11. Once all equations are exhausted. we are done!
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool evaluate();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // A debug helper class (Enabled by defining PDEBUG #define PDEBUG)
    void print();

    protected:
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Protected constructor to prevent any explicit instantiation.
    EquationEvaluator();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Evaluate a variable / equation associated with name.
    // Recurse if needed until each variable within an equation is successfully evaluated.
    // By the time this function returns, the equation in the MAP associated with the name (argument)
    // is successfully evaluated.
    bool evaluate(std::string name);
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // This method is a helper to retrieve the calculated value of a variable (denoted by name) that is assigned
    //  to a given equation.
    std::string getValue(std::string name);


    static EquationEvaluator *m_pInstance;
    
    protected:
    EqMap m_equations;

};


#endif  //  __EQ_EVALUATOR__