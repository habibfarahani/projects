#include "EquationParser.h"

#include <iostream>
#include <sstream>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Various error strings that will be assigned to m_lastError string depending of error type.

const char ERROR_PARSING_EQUATION[]     =   "[ERROR] Parsing equation ";
const char ERROR_INVALID_EQ_PARAM[]     =   "[ERROR] Invalid Equation Parameter ";
const char ERROR_OPENING_FILE[]         =   "[ERROR] Opening input file ";
const char ERROR_NON_UNIQUE_ANSWER[]    =   "[ERROR] Non unique answers ";
const char ERROR_UNRESOLVED_PARAM[]     =   "[ERROR] Unresolved parameter ";
const char ERROR_CIRCULAR_DEP[]         =   "[ERROR] Variable Circular Depedency for ";
const char ERROR_INVALID_EQUATION[]     =   "[ERROR] Invalid Equation shuld be (LHS = RHS) ";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inserts an parameter (identified by a name) in the equation and will add the equation to the MAP.
bool EquationParser::insert(Equation *eq, std::string name, EqMap &eqMap)
{
    bool status = false;

    // Is this parameter an operator (+)?
    if(EquationParams::isOperator(name))
    {
        EqMap::iterator it = eqMap.begin();
        Operators *pOpt = nullptr;
        
        // Before creating a new instance check all the MAP and see if we already have
        //  this oprator created.
        while((it != eqMap.end()) && (pOpt == nullptr))
        {
            pOpt = it->second->getOperator(name);
            it++;
        }

        // Did we find this operator
        if(pOpt == nullptr)
        {
            //  We did not find this operator anywhere in the map
            // so create it which also inserts it i the VECTOR of operators
            status = eq->createOperator(name);
        }
        else
        {
            // Found an operator already, so insert it in the VECTOR (of operator pointers)
            status = eq->insert(pOpt);
        }
        
    }
    else if(EquationParams::isVariable(name) ||
            EquationParams::isLiteralConst(name))
    {
        EqMap::iterator it = eqMap.begin();
        EquationParams *pParam = nullptr;

        // Search the entire map to see if this parameter already exists
        while((it != eqMap.end()) && (pParam == nullptr))
        {
            pParam = it->second->getParameter(name);
            it++;
        }

        // Did we find this parameter
        if(pParam == nullptr)
        {
            // Parameter is not found so create one and insert in VECTOR
            status = eq->createParameters(name);
        }
        else
        {
            // Parameter is foudn so insert it into the VECTOR
            status = eq->insert(pParam);
        }

    }
    else
    {
        // Invalid parameters.  Valid params are:
        //    + for operators
        //    digits (0-9) for literal constants.
        //    alpha (a-z, A-Z) for variable names.
        //     All other combinations are invalid.
        m_lastError = ERROR_INVALID_EQ_PARAM;
        m_lastError += "(";
        m_lastError += name;
        m_lastError += ")\n";
    }

    return status;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Creates an equation and if the basic sanity check (see below) is passed, it will be inserted in the MAP.
// Otherwise, it will be deleted with an error reported to the caller.
bool EquationParser::createEquation(std::vector<std::string> &arr, EqMap &eqMap)
{
    Equation *eq = new Equation();

    // A Valid equation is composed of:
    // LHS (which is always a variable) index 0
    // = (must have)    index 1
    // RHS (which is a combination of variables, literals and operators.)
    if(eq)
    {
        // Do we have a variable in index 0?
        if(EquationParams::isVariable(arr[0]))
        {
            //  Do we have an equal sign in index 1?
            if(EquationParams::isEqual(arr[1]))
            {
                size_t i=2;
                bool success = true;;

                while(i<arr.size() && (success))
                {
                    success = insert(eq, arr[i], eqMap );
                    i++;
                }
                // If we have successfully parsed the array (split) and
                // Equation is verified then insert this element into the map
                if(eq->verify() && success)
                { 
//                    printf("%s => ", arr[0].c_str());
//                    eq->print();
                    
                    // If there are no other instance of an equation assigned to the variable them=n we are good.
                    if(eqMap.find(arr[0]) == eqMap.end())
                    {
                        eqMap.insert(std::make_pair(arr[0], eq));
                        return true;
                    }
                    else
                    {
                        m_lastError = ERROR_NON_UNIQUE_ANSWER;
                        m_lastError += "(";
                        m_lastError += arr[0];
                        m_lastError += ")";
                    }
                }
                // else
                // {
                //     m_lastError += ERROR_PARSING_EQUATION;
                //     m_lastError += "(";
                //     m_lastError += arr[0];
                //     m_lastError += ")";
                // }
            }
        }
        m_lastError += ERROR_PARSING_EQUATION;
        m_lastError += "(";
        m_lastError += arr[0];
        m_lastError += ")";
        delete eq;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Overloaded parse routine that eplits a line of input file into an array of strings.
bool EquationParser::parse(std::string &line, std::vector<std::string> &arr)
{
    std::stringstream ss(line);

    // Entry point into parser.  Clear all last errors
    m_lastError.clear();

    for(std::string s; ss >> s;)
    {
        arr.push_back(s);
    }

    if(arr.size() > 2)
    {
        return true;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Overloaded parse that populates the equations MAP with the appropriate equations
bool EquationParser::parse(EqMap &eqMap)
{
    bool status = false;

    if(m_sName.size())
    {
        std::ifstream inFile;
        std::string line;

        inFile.open(m_sName, std::ios::in);

        // Make sure the file is successfully opened
        if(inFile.is_open())
        {
            status = true;
            while(!inFile.eof() && (true == status))
            {
                // Read the current line in the file till the end
                getline(inFile, line);
                // If line any data then parse it
                if(line.size())
                {
                    std::vector<std::string> arr;
                    if(parse(line, arr))
                    {
                        status = createEquation(arr, eqMap);
                    }
                    else
                    {
                        m_lastError = ERROR_INVALID_EQUATION;
                        m_lastError += "(";
                        m_lastError += line;
                        m_lastError += ")";
                        status = false;     // Flag an error
                    }
                }
            }

            inFile.close();

            // If all is good then verify the map otherwise, we have already encountered an error
            if(status)
            {
                status = verify(eqMap);
            }
        }
        else
        {
            // If file is not found then report and error and exit
            m_lastError = ERROR_OPENING_FILE;
            m_lastError += m_sName;

        }
    }

    return status;
}

bool EquationParser::checkUnresolvedRef(std::string name, EqMap &eqMap)
{
    if(eqMap.find(name) == eqMap.end())
    {
        m_lastError = ERROR_UNRESOLVED_PARAM;
        m_lastError += "(";
        m_lastError += name;
        m_lastError += ")";

        return true;
    }
    else
    {
         
    }

    return false;

}

void printArr(std::vector<std::string> &depArr)
{
#ifdef PDEBUG
    printf("DEP:: ");
    for(size_t i=0; i<depArr.size(); i++)
    {
        printf("[%s]->", depArr[i].c_str());
    }

    printf("\n");
#endif
}




bool EquationParser::findDuplicate(std::string element, std::vector<std::string> &depArr)
{
    size_t arrSize = depArr.size();

    if(arrSize > 1)
    {
        size_t i = 0;

        while(i < arrSize)
        {
            if(depArr[i] == element)
            {
                return true;
            }

            i++;
        }
    }

    return false;
}

bool EquationParser::circularIndep(std::vector<std::string> &depArr, Equation *pEq, EqMap &eqMap)
{
    bool success = true;

    if(!pEq->getNumVariables())
    {
        // This 
        depArr.pop_back();
        printArr(depArr);
        pEq->print();
    }
    else
    {

        paramsVect params = pEq->getParameters();
        size_t i = 0;

        while(i < params.size() && success)
        {
            if(params[i]->isVariable())
            {
                if(findDuplicate(params[i]->getName(), depArr))
                {
                    m_lastError = ERROR_CIRCULAR_DEP;
                    m_lastError += "(";
                    m_lastError += params[i]->getName();
                    m_lastError += ")";
                    printArr(depArr);
                    success = false;
                }
                else
                {
                    depArr.push_back(params[i]->getName());
                    printArr(depArr);
                    EqMap::iterator it = eqMap.find(params[i]->getName());
                    if(it != eqMap.end())
                    {
                        success = circularIndep(depArr, it->second, eqMap);
                    }
                }            
            }
            i++;
        }
        pEq->print();
    }

    return success;

}


bool EquationParser::circularIndep(std::vector<std::string> &depArr, EqMap &eqMap)
{

    EqMap::iterator it = eqMap.begin();
    bool success = true;

    while(it != eqMap.end() && success)
    {

//        printf("Processing EQ: %s = ", it->first.c_str());
//        it->second->print();
        depArr.push_back(it->first);
        printArr(depArr);
        success = circularIndep(depArr, it->second, eqMap);

        depArr.clear();
        it++;
    }

    return success;

}

//////////////////////////////////////////////////////////////////////////////

bool EquationParser::verify(EqMap &eqMap)
{

// It will verify each equation
// Makes sure there are no unrefereced variables.
// Makes sure there are no circular variable dependecies
    EqMap::iterator it = eqMap.begin();

    while(it != eqMap.end())
    {
        paramsVect params = it->second->getParameters();
        size_t i = 0;

        while(i < params.size())
        {
            if(params[i]->isVariable())
            {
                if(true == checkUnresolvedRef(params[i]->getName(), eqMap))
                {
                    return false;       // Verification failed due to unresolved ref
                }
            }
            i++;
        }
        it++;
    }
 
    //  If we are here then we did not find any unresolved ref.
    //  So check for cicular independence which means no variable
    //  dependency should be as such so that it will depend on itself.
    std::vector<std::string> depArr;
    return circularIndep(depArr, eqMap);

}


bool EquationParser::onError()
{
    bool status = false;

    if(m_sName.size())
    {
        std::ifstream inFile;
        std::string line;
        printf("-----------------------------------\n");
        if(m_lastError.size())
        {
            printf("%s\n", m_lastError.c_str());
        }

        inFile.open(m_sName, std::ios::in);

        if(inFile.is_open())
        {
            while(!inFile.eof())
            {
                getline(inFile, line);

                if(line.size())
                {
                    printf("%s\n", line.c_str());
                }
            }

            inFile.close();
        }
    }

    return status;

}

