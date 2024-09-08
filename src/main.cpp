#include <iostream>

#include "ExpressionCalc.hpp"

mathSymbolMap_t mathSymbols;

int main(void) 
{
    ExpressionPart expp(Symbol(SymbolPriority::OP_MULTIDIV, nullptr));
    std::string str("1234.5---233.99");
    auto iter = str.crbegin();
    auto rbeg = iter;
    std::cout << phaseDigit(iter) << std::endl 
              << iter - rbeg << std::endl
              << expp.m_op.m_priority << std::endl;

}
