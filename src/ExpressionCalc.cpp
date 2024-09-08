#include "ExpressionCalc.hpp"

#include <sstream>
#include <stack>
#include <algorithm>

extern mathSymbolMap_t mathSymbols;

bool isPartOfSymbol(std::string str)
{
    for (auto iter = mathSymbols.cbegin(); iter != mathSymbols.cend(); ++iter)
    {
        if (iter->first.find(str) != std::string::npos)
            return true;
    }
    return false;
}
bool isVaildSymbol(std::string str)
{
    for (auto iter = mathSymbols.cbegin(); iter != mathSymbols.cend(); ++iter)
    {
        if (str == iter->first)
            return true;
    }
    return false;
}

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
    map["/"].func_p = static_cast<BinaryOpFunc_t*>([](double n1, double n2) -> double { return n1/n2; });
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

std::string phaseSymbol(std::string::const_iterator &iter, const std::string &exp)
{
    // TODO: fix bug: when there is a symbol (e.g., rbracket) at the last of exp, the function couldn't phase it.

    auto beg = iter;

    for ( ++iter; *iter != '\0'; ++iter)
    {
        std::string str(beg, iter);
        if (isPartOfSymbol(str))
        {
            if (isVaildSymbol(str))
            {
                return str;
            }
            else
                continue;
        }
        else 
            throw std::runtime_error("Unknown symbol \"" + str + "\".");
    }
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
            std::string symStr = phaseSymbol(iter, exp);
            Symbol sym;

            sym = mathSymbols.at(symStr);

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

double evalSuffixExpDeque(std::deque<ExpressionPart> suffix_exp)
{
    std::stack<double> nums;

    while (suffix_exp.size() != 0)
    {
        auto deque_front = suffix_exp.front();

        if (deque_front.m_type == NUMBER)
        {
            nums.push(deque_front.m_num);
        }
        else {
            if (nums.size() < 2)
                throw std::runtime_error("Invaild expression!");

            auto stack_top = nums.top();
            nums.pop();
            auto stack_sec_top = nums.top();
            nums.pop();

            nums.push(deque_front.m_op.func_p(stack_sec_top, stack_top));
        }

        suffix_exp.pop_front();
    }
    return nums.top();
}

std::string suffixExpDequeToStr(std::deque<ExpressionPart> suffix_exp)
{
    std::ostringstream oss;

    while (suffix_exp.size() != 0)
    {
        auto deque_front = suffix_exp.front();
        if (deque_front.m_type == NUMBER)
            oss << deque_front.m_num << ' ';
        else 
            oss << deque_front.m_op.name << ' ';

        suffix_exp.pop_front();
    }

    return oss.str();
}
