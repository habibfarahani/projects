#include <stdio.h>
#include "Equation.h"

#include "Add.h"
#include "Subtract.h"
#include "Variable.h"
#include "Constant.h"
#include <algorithm> // for std::all_of
#include <cctype>    // for std::isdigit
#include <regex> // for std::regex_match

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Constructor
Equation::Equation()
{
    m_bNeedOperator = false;
    m_numVariables = -1;        // It is not initialized
    m_value.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// To delete these values it is best to use a unique_ptr object or a smart pointer
Equation::~Equation()
{
    for(size_t i=0; i<m_params.size(); i++)
    {
        if(m_params[i]->toDelete())
        {
            delete m_params[i];
        }
    }

    m_params.clear();

    for(size_t i=0; i<m_operators.size(); i++)
    {
        if(m_operators[i]->toDelete())
        {
            delete m_operators[i];
        }
    }
    m_operators.clear();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Returns the total number of variables (not constants) in this equation.
/// The count loop enters only once if the number is uninitialized (=-1)
int Equation::getNumVariables()
{
    if(m_numVariables < 0)
    {
        m_numVariables = 0;
        for(size_t i=0; i<m_params.size(); i++)
        {
            if(m_params[i]->isVariable())
            {
                m_numVariables++;
            }
        }
    }

    return m_numVariables;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Returns a pointer to a parameter denoted by name in the params VECTOR
EquationParams *Equation::getParameter(const std::string &name)
{
    size_t i=0;
    EquationParams *pParam = nullptr;

    while(i<m_params.size() && (pParam == nullptr))
    {
        if(m_params[i]->getName() == name)
        {
            pParam = m_params[i];
        }
        i++;
    }
    return pParam;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Returns a pointer to an operator denoted by name in the params VECTOR
Operators *Equation::getOperator(const std::string &name)
{
    size_t i=0;
    Operators *pOpt = nullptr;

    while(i<m_operators.size() && (pOpt == nullptr))
    {
        if(m_operators[i]->getName() == name)
        {
            pOpt = m_operators[i];
        }
        i++;
    }
    return pOpt;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Returns true if a new operator was created and successfully inserted
bool Equation::createOperator(const std::string &str)
{
    Operators *pOpt = nullptr;

    if(EquationParams::isOperator(str))
    {
        if(str == "+")
        {
            pOpt = new Add();
        }
        // Though subtraction is not required.  It is easy to implement
        // if(str == "-")
        // {
        //     pOpt = new Subtract();
        // }
    }

    return insert(pOpt);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Returns true if a new parameter was created and successfully inserted
bool Equation::createParameters(const std::string &str)
{
    EquationParams *pPrams = nullptr;

    if(EquationParams::isLiteralConst(str))
    {
        pPrams = new LiteralConstant(str);
    }
    else if(EquationParams::isVariable(str))
    {
        pPrams = new Variable(str);
    }

    return insert(pPrams);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Verifies an equation
bool Equation::verify()
{
    if(m_bNeedOperator && m_params.size())
    {
        if((m_params.size() == 1) && (m_operators.empty()))
        {
            return true;
        }
        else if((m_params.size() > 1) && (m_params.size() == (m_operators.size() + 1)))
        {
            return true;
        }

    }
    return false;

}


void Equation::print()
{
#ifdef PDEBUG
    if(verify())
    {
        printf("This EQ IS: ---> ");
        for(size_t i=0; i<m_params.size(); i++)
        {
            printf("%s ", m_params[i]->getName().c_str());
            if(i<m_operators.size())
            {
                printf("%s ", m_operators[i]->getName().c_str());
            }

        }

        printf(" = %s <<<<<\n", m_value.c_str());
    }
#endif
}

bool Equation::insert( EquationParams *pParam)
{
    if(pParam)
    {
        if(!m_bNeedOperator)
        {
            m_params.push_back(pParam);
            m_bNeedOperator = true;
            pParam->use();
            return true;
        }
    }

    return false;

}


bool Equation::insert( Operators *pOpt)
{
    if(pOpt)
    {
        if(m_bNeedOperator)
        {
            m_operators.push_back(pOpt);
            m_bNeedOperator = false;

            return true;
        }
    }

    return false;


}

