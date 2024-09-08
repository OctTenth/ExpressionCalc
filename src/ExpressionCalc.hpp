#ifndef EXPRESSION_CALC_HPP__
#define EXPRESSION_CALC_HPP__

#include <string>
#include <stack>
#include <deque>
#include <map>
#include <cmath>
#include <cctype>
#include <climits>

// typedef double (AlphaSymbol_t)();
// typedef double (UnaryOp_t)(double);
typedef double (BinaryOpFunc_t)(double, double);

enum ExpressionPartType {
    NUMBER, OPERATOR
};

enum SymbolPriority {
    OP_PLUSMINUS  = 0x00,
    OP_MULTIDIV   = 0x01,
    OP_FUNC       = 0x02,
    OP_POWER      = 0x03,

    SY_BRACKET    = INT_MAX,
    SY_SYMBOL     = 0x0100
};

struct Symbol {
    SymbolPriority m_priority;
    BinaryOpFunc_t *func_p;

    Symbol(void) = default;
    Symbol(SymbolPriority priority, BinaryOpFunc_t* func_pointer)
        : m_priority(priority), func_p(func_pointer) {};
    ~Symbol() = default;
};

struct ExpressionPart {
    ExpressionPartType m_type;
    union {
        double m_num;
        Symbol m_op;
    };
    
    ExpressionPart(void) = default;
    ExpressionPart(double number): m_type(ExpressionPartType::NUMBER), m_num(number) {};
    ExpressionPart(Symbol sym): m_type(ExpressionPartType::OPERATOR), m_op(sym) {};
};

typedef std::map<std::string, Symbol> mathSymbolMap_t;

int mathSymbolsInit(mathSymbolMap_t map);
std::string phaseDigit(std::string::const_reverse_iterator &riter);
std::stack<ExpressionPart> strToSuffixExpList(const std::string exp);


#endif
