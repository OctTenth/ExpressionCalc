#include <iostream>

#include "ExpressionCalc.hpp"

mathSymbolMap_t mathSymbols;

int main(void) 
{
    mathSymbolsInit(mathSymbols);
    ExpressionPart expp(Symbol(SymbolPriority::OP_MULTIDIV, nullptr));
    std::string str("1234.5-(233.99+444.22*66)");
    auto iter = str.cbegin();
    auto beg = iter;
    auto sufexp = strToSuffixExpDeque(str);
    std::cout << phaseDigit(iter) << std::endl 
              << phaseSymbol(iter) << std::endl
              << iter - beg << std::endl
              << suffixExpDequeToStr(sufexp) << std::endl;

}
