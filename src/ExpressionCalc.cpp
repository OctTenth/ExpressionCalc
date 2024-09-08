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

std::string phaseDigit(std::string::const_iterator &iter)
{
    auto beg = iter;
    for ( ; isdigit(*iter) || *iter == '.'; ++iter)
    {
        continue;
    }
    
    return std::string(beg, iter);
}

std::deque<ExpressionPart> strToPrefixExpStack(const std::string exp)
{
    std::deque<ExpressionPart> s1, ops;
    auto iter = exp.cbegin();

    while (iter != exp.cend())
    {
        if (std::isspace(*iter)) {
	    ++iter;
            continue;
        } else if (std::isdigit(*iter)) {
            s1.emplace_back(std::stod(phaseDigit(iter)));
        } else {
	  // TODO: Symbol detect  
	}
    }

    return s1;
}
