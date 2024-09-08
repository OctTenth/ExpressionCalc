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

std::string phaseDigit(std::string::const_reverse_iterator &riter)
{
    auto rbeg = riter;
    for ( ; isdigit(*riter) || *riter == '.'; ++riter)
    {
        continue;
    }
    
    return std::string(riter.base(), rbeg.base());
}

std::stack<ExpressionPart> strToPrefixExpStack(const std::string exp)
{
    std::stack<ExpressionPart> s1, ops;
    auto iter = exp.crbegin();

    while (iter != exp.crend())
    {
        if (std::isspace(*iter)) {
	    ++iter;
            continue;
        } else if (std::isdigit(*iter)) {
            s1.emplace(std::stod(phaseDigit(iter)));
        } else {
	  // TODO: Symbol detect  
	}
    }

    return s1;
}
