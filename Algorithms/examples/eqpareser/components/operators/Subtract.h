#ifndef __EQ_SUBTRACT_OP__
#define __EQ_SUBTRACT_OP__

#include "Operators.h"

class Subtract : public Operators
{
    public:
    Subtract()
    {
        m_name = "-";
    };
    ~Subtract(){};

    std::string evaluate(std::string &lhs, std::string &rhs);

};


#endif  //__EQ_SUBTRACT_OP__