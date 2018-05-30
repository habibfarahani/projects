#ifndef __EQ_ADD_OP__
#define __EQ_ADD_OP__

#include "Operators.h"

class Add : public Operators
{
    public:
    Add()
    {
        m_name = "+";
    };
    ~Add(){};

    std::string evaluate(std::string &lhs, std::string &rhs);

};


#endif  //__EQ_ADD_OP__
