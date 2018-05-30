#ifndef __EQ_CONSTANT__
#define __EQ_CONSTANT__

#include "Params.h"

class LiteralConstant : public EquationParams
{
    public:
    LiteralConstant(const std::string str) : EquationParams(str) {};
    virtual ~LiteralConstant(){};
    virtual bool isLiteral() {return true;}

};



#endif //__EQ_CONSTANT__