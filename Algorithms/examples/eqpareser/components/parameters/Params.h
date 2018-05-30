#ifndef __EQ_PARAMS__
#define __EQ_PARAMS__

#include <vector>
#include <map>
#include <string>

//#define PDEBUG
class EquationParams
{
    public:
    EquationParams(const std::string str)
    {
        m_name = str;
        m_ref = 0;
    }

    virtual ~EquationParams()
    {
    };

    void use()
    {
        m_ref++;
    }

    bool toDelete()
    {
        m_ref--;
        if(m_ref < 1)
        {
            return true;
        }

        return false;
    }

    std::string &getName()
    {
        
        return m_name;
    }

    // std::string &getValue()
    // {
    //     return m_value;
    // }

    // void setValue(std::string str)
    // {
    //     m_value = str;
    // }

    // bool isEvaluated()
    // {
    //    if(m_value.size()) 
    //    {
    //        return true;
    //    }

    //    return false;
    // }

    virtual bool isVariable() {return false;}
    virtual bool isLiteral() {return false;}

//    virtual bool range() = 0;

    static bool isVariable(const std::string &str);
    static bool isLiteralConst(const std::string &str);
    static bool isOperator(const std::string &str);
    static bool isEqual(const std::string &str);

    protected:
    std::string m_name;
    int m_ref;
//    std::string m_value;
};



#endif  //  __EQ_PARAMS__
