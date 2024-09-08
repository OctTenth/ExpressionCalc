#include <iostream>

#include "ExpressionCalc.hpp"

mathSymbolMap_t mathSymbols;

int main(void) 
{
    ExpressionPart expp(Symbol(SymbolPriority::OP_PLUSMINUS, nullptr));
    std::cout << phaseDigit("1234 +++") << std::endl
              << expp.m_op.m_priority << std::endl;

}
