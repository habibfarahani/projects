#include "Equation.h"
#include "EquationEvaluator.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Initialize the static instance

EquationEvaluator *EquationEvaluator::m_pInstance = NULL;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
EquationEvaluator::EquationEvaluator()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// cleanup the map before destrying this object
EquationEvaluator::~EquationEvaluator()
{
    std::map<std::string, Equation *>::iterator it = m_equations.begin();

    while(it != m_equations.end())
    {
        Equation *pEq = it->second;
        it++;
    printf("DELETING\n");
        if(pEq)
        {
            delete pEq;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Instance method to ensure that only and only one object will always be created.
EquationEvaluator &EquationEvaluator::Instance()
{
    if(!m_pInstance)
    {
        m_pInstance = new EquationEvaluator();
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Get the value of the variable with name (name)
std::string EquationEvaluator::getValue(std::string name)
{
    std::string value;
    std::map<std::string, Equation *>::iterator it = m_equations.find(name);

    if(it != m_equations.end())
    {
        value = it->second->getValue();
    }

    return value;    
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Overloaded evaluation method using a variable name.  It will recurse until a value for a variable is found.
bool EquationEvaluator::evaluate(std::string name)
{
    
    // Find an equation associated with this variable.
    std::map<std::string, Equation *>::iterator it = m_equations.find(name);

    if(it != m_equations.end())
    {
        if(!it->second->isEvaluated())
        {
            // Go through the list of parameters and operators
            // IN case of a variable, recursively find the value
            // and continue evaluating the equation            
            paramsVect params = it->second->getParameters();
            operatorsVect operators = it->second->getOperators();
            std::string currentValue;
            std::string newValue;

            // We need two parameters at a time to ensure that we can perform the operation.
            // Start with param at index 0;
            if(params[0]->isVariable())
            {
                // If it is a variable, then start the recursion.
                evaluate(params[0]->getName());
                currentValue = getValue(params[0]->getName());
            }
            else
            {
                // otherwise use this as the first value
                currentValue = params[0]->getName();
            }

            // Go through all the operators and get the next value
            for(size_t i=0; i<operators.size(); i++)
            {

                if(params[i+1]->isVariable())
                {
                    // If it is a variable recurse to get the value ans toreit in New vlue
                    evaluate(params[i+1]->getName());
                    newValue = getValue(params[i+1]->getName());
                    it->second->print();
                }
                else
                {
                    newValue = params[i+1]->getName();
                }
                // At this time we have the currentvalue and new value so perform the operation
                // and store the result in current value for next operation
                currentValue = operators[i]->evaluate( currentValue, newValue);

            }
            // When we are here, we are done with the equation so store the value.
            it->second->setValue(currentValue);
//            it->second->print();
        }
    }
    else
    {
        return false;
    }

    return true;    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The entry into evaluate method where for each function, the logic resurses to find the value of the appropriate variable.
bool EquationEvaluator::evaluate()
{
    bool status = true;
    std::map<std::string, Equation *>::iterator it = m_equations.begin();

    while(it != m_equations.end() && (true == status))
    {
        status = evaluate(it->first);
        it++;
    }

    return status;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// When all goes well this method is called to print the entire results.
void EquationEvaluator::print()
{
    std::map<std::string, Equation *>::iterator it = m_equations.begin();

    while(it != m_equations.end())
    {
        printf("%-15s = [%s]\n", it->first.c_str(), it->second->getValue().c_str());
        it++;
    }
}

