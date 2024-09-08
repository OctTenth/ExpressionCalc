#include "ExpressionCalc.hpp"

int mathSymbolsInit(std::map<std::string, Symbol> map)
{
    map["+"].priority = 3;
    map["+"].func_p = static_cast<BinaryOpFunc_t*>([](double n1, double n2) -> double { return n1+n2; });
    map["-"].priority = 3;
    map["-"].func_p = static_cast<BinaryOpFunc_t*>([](double n1, double n2) -> double { return n1-n2; });
    map["*"].priority = 2;
    map["*"].func_p = static_cast<BinaryOpFunc_t*>([](double n1, double n2) -> double { return n1*n2; });
    map["/"].priority = 2;
    map["/"].func_p = static_cast<BinaryOpFunc_t*>([](double n1, double n2) -> double { return n1*n2; });
    map["^"].priority = 1;
    map["^"].func_p = static_cast<BinaryOpFunc_t*>([](double n1, double n2) -> double { return std::pow(n1, n2); });
}