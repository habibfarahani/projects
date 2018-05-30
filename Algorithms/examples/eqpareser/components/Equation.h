#ifndef __EQUATION__
#define __EQUATION__



#include "Variable.h"
#include "Constant.h"
#include "Operators.h"

class EquationParams;
class BaseOperators;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Data structure definitions for Equation Object:
/// paramsVect: is a vector of EquationParams objects that mainly are either constant literals (unsigned int in this example)
/// or variables (that should have been defined by a corresponding equation).
/// operatorsVect: is a vector of operators (+ in this example) that exist in a given Equation instantiation.
///
/// Example:  For an equation with following syntax 
///             Var1 = 25 + Var2 + Var3 + 8
/// The data structures look like:
///     paramsVect           operatorsVect
///       25                    +
///       Var2                  +
///       Var3                  +
///       8                    
/// Also note that number of operators should always be one less than number of parameters.  
/// This is one of verification criteria within Equation object.
typedef std::vector<EquationParams *> paramsVect;
typedef std::vector<Operators *> operatorsVect;

class Equation
{
    public:
    Equation();

    ~Equation();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// returns true if a value has been set for this equation
    bool isEvaluated()
    {
        if(m_value.size())
        {
            return true;
        }

        return false;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Overloaded insert methods used primarily by Equation Parser object.
    /// Note that only one instance of parameters and operato objects are created at a time.
    /// For example, if an equaion had 10 + operators only one instance is created and used across all equation(s)
    /// Or if for a set of equations like:
    ///     Var1 = Var2 + 3 + 9
    ///     Var2 = 7 
    ///     Only one Var2 shall be created.
    bool insert( EquationParams *pParam);
    bool insert( Operators *pOpt);

    void print();
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Returns true if the current equation is correct.
    bool verify();
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Get the value assigned to this equation.
    std::string &getValue()
    {
        return m_value;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Set the value assigned to this equation.
    void setValue(const std::string &val)
    {
        m_value = val;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Returns a reference to the internal parameter VECTOR
    paramsVect &getParameters()
    {
        return m_params;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Returns a reference to the internal Operators VECTOR
    operatorsVect &getOperators()
    {
        return m_operators;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Returns number of variables in internal parameter VECTOR (ONLY)
    int getNumVariables();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Resturns a given parameter identified by name
    EquationParams *getParameter(const std::string &name);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Resturns a given Operator identified by name
    Operators *getOperator(const std::string &name);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// Creator Methods that also insert the appropriate value in the internal VECTOR objects
    bool createOperator(const std::string &str);
    bool createParameters(const std::string &str);

    private:
    paramsVect m_params;
    operatorsVect m_operators;

    std::string m_value;

    int m_numVariables;
    bool m_bNeedOperator;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// This data structure is used by both Equation Parser and Equation Evauator objects.
///  A set of equations like:
///     Var1 = 3 + Var2 + Var3 + 7
///     Var4 = Var1 + 8
///     Var2 = Var3 + 6
///     Var3 = Var4 + 2
///
///   Shall be represented by the MAP as such:
///     KEY                         VALUE
///     Var1            Equation {paramsVect: {3, Var2, Var3, 7}    operatorsVect: {+,+,+}}
///     Var2            Equation {paramsVect: {Var3, 6}             operatorsVect: {+}}
///     Var3            Equation {paramsVect: {Var4, 2}             operatorsVect: {+}}
///     Var4            Equation {paramsVect: {Var1 + 8}            operatorsVect: {+}}
///
typedef std::map<std::string, Equation *> EqMap;


#endif //__EQUATIONS__