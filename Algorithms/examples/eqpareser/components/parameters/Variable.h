#ifndef __EQ_VARIABLE__
#define __EQ_VARIABLE__

#include "Params.h"

class Variable : public EquationParams
{
    public:
    Variable(const std::string str) : EquationParams(str){};
    virtual ~Variable(){};
    virtual bool isVariable() {return true; }

};

#endif //__EQ_VARIABLE__