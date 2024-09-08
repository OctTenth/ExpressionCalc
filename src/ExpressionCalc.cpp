#include "ExpressionCalc.hpp"

#include <sstream>

extern mathSymbolMap_t mathSymbols;

int mathSymbolsInit(mathSymbolMap_t &map)
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

    map["("].m_priority = SymP::SY_LBRACKET;
    map["("].func_p = nullptr;
    map[")"].m_priority = SymP::SY_RBRACKET;
    map[")"].func_p = nullptr;

    for (auto map_iter = mathSymbols.begin(); map_iter != mathSymbols.end(); ++map_iter)
    {
        map_iter->second.name = map_iter->first.c_str();
    }

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

std::string phaseSymbol(std::string::const_iterator &iter)
{
    std::set<std::string> op_set;

    for ( auto mapIter = mathSymbols.cbegin(); mapIter != mathSymbols.cend(); mapIter++)
    {
        auto sym = mapIter->first;
        if (sym.length() == 1) {
            op_set.insert(sym);
        }
    }

    auto beg = iter;

    if (op_set.find(std::string() + *iter) != op_set.end()) {
        ++iter;
        return std::string(beg, iter);
    }

    for ( ; (std::isalpha(*iter)); ++iter)
    {
        continue;
    }
    
    return std::string(beg, iter);
}

void symPushToStack(std::deque<ExpressionPart> &s1, std::deque<ExpressionPart> &ops, Symbol &sym)
{
    if (sym.m_priority > SY_BRACKET)
    {
        if (sym.m_priority == SY_LBRACKET)
        {
            ops.push_back(ExpressionPart(sym));
            return;
        }
        else 
        {
            while (true)
            {
                if (ops.back().m_op.m_priority == SY_LBRACKET)
                { ops.pop_back(); return; }
                
                s1.push_back(ops.back());
                ops.pop_back();
            }
        }
    }

    while (true) {
        if (ops.size() == 0 || 
                ops.back().m_op.m_priority == SymbolPriority::SY_LBRACKET ||
                sym.m_priority > ops.back().m_op.m_priority)
        {
            ops.push_back(ExpressionPart(sym));
            return;
        }
        else {
            s1.push_back(ops.back());
            ops.pop_back();
        }
    }
}

std::deque<ExpressionPart> strToSuffixExpDeque(const std::string exp)
{
    std::deque<ExpressionPart> s1, ops;
    auto iter = exp.cbegin();

    while (iter != exp.cend())
    {
        if (std::isspace(*iter)) {
	        ++iter;
            continue;
        } else if (std::isdigit(*iter) || *iter == '.') {
            s1.emplace_back(std::stod(phaseDigit(iter)));
            continue;
        } else {
            std::string symStr = phaseSymbol(iter);
            Symbol sym;

            try {
                sym = mathSymbols.at(symStr);
            } catch (std::out_of_range &e) {
                throw std::out_of_range("Unknown symbol \"" + symStr + "\".");
            }
            
            symPushToStack(s1, ops, sym);
	    }
    }

    while (ops.size() != 0)
    {
        s1.push_back(ops.back());
        ops.pop_back();
    }

    return s1;
}

std::string suffixExpDequeToStr(std::deque<ExpressionPart> suffix_exp)
{
    std::ostringstream oss;

    while (suffix_exp.size() != 0)
    {
        auto d_front = suffix_exp.front();
        if (d_front.m_type == NUMBER)
            oss << d_front.m_num << ' ';
        else 
            oss << d_front.m_op.name << ' ';

        suffix_exp.pop_front();
    }

    return oss.str();
}
