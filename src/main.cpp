#include <iostream>

#include "ExpressionCalc.hpp"

mathSymbolMap_t mathSymbols;

int main(int argc, char **argv) 
{
    mathSymbolsInit(mathSymbols);
    std::string str;
    std::cin >> str;
    std::cout << "> " << evalSuffixExpDeque(strToSuffixExpDeque(str)) << std::endl;
}
