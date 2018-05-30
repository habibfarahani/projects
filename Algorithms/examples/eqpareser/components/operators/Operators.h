#ifndef __EQ_OPERATORS__
#define __EQ_OPERATORS__

#include <string>


class Operators
{
    public:
    Operators(){m_ref = 0;};
    virtual ~Operators(){};

    std::string &getName()
    {
        return m_name;
    }

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


    virtual std::string evaluate(std::string &lhs, std::string &rhs) = 0;

    protected:
    std::string m_name;
    int m_ref;
};





#endif  //  __EQ_PARAMS__
