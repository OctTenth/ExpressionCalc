#include "ExpressionCalc.hpp"

int mathSymbolsInit(mathSymbolMap_t map)
{
    using SymP = SymbolPriority;

    map["+"].m_priority = SymP::OP_PLUSMINUS;
    map["+"].func_p = static_cast<BinaryOpFunc_t*>([](double n1, double n2) -> double { return n1+n2; });
    map["-"].m_priority = SymP::OP_PLUSMINUS;
    map["-"].func_p = static_cast<BinaryOpFunc_t*>([](double n1, double n2) -> double { return n1-n2; });
    map["*"].m_priority = SymP::OP_MULTIDIV;
    map["*"].func_p = static_cast<BinaryOpFunc_t*>([](double n1, double n2) -> double { return n1*n2; });
    map["/"].m_priority = SymP::OP_MULTIDIV;
    map["/"].func_p = static_cast<BinaryOpFunc_t*>([](double n1, double n2) -> double { return n1*n2; });
    map["^"].m_priority = SymP::OP_POWER;
    map["^"].func_p = static_cast<BinaryOpFunc_t*>([](double n1, double n2) -> double { return std::pow(n1, n2); });

    map["("].m_priority = SymP::SY_BRACKET;
    map["("].func_p = nullptr;
    map[")"].m_priority = SymP::SY_BRACKET;
    map[")"].func_p = nullptr;

    return 0;
}

std::string phaseDigit(const std::string str)
{
    std::string::const_iterator iter;

    for ( iter = str.begin(); isdigit(*iter) || *iter == '.'; iter++)
    {
        continue;
    }
    
    return std::string(str.cbegin(), iter);
}

std::stack<ExpressionPart> strToSuffixExpList(const std::string exp)
{
    std::stack<ExpressionPart> s1, ops;

    for (auto iter = exp.begin(); iter != exp.end(); ++iter)
    {
        if (std::isspace(*iter)) {
            continue;
        }
        else if (std::isdigit(*iter)) {
            s1.emplace(std::stod(phaseDigit(std::string(iter, exp.end()))));
        }
    }

    return s1;
}
