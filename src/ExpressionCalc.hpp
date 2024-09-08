#ifndef EXPRESSION_CALC_HPP__
#define EXPRESSION_CALC_HPP__

#include <string>
#include <deque>
#include <map>
#include <set>
#include <cmath>
#include <cctype>
#include <climits>
#include <stdexcept>

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

    SY_BRACKET    = INT_MAX - 2,
    SY_LBRACKET   = INT_MAX - 1,
    SY_RBRACKET   = INT_MAX,
    SY_ALPHANUM   = 0x0100
};

struct Symbol {
    const char *name;
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
    ~ExpressionPart(void) = default;
};

typedef std::map<std::string, Symbol> mathSymbolMap_t;

int mathSymbolsInit(mathSymbolMap_t &map);
std::string phaseDigit(std::string::const_iterator &iter);
std::string phaseSymbol(std::string::const_iterator &iter);
std::deque<ExpressionPart> strToSuffixExpDeque(const std::string exp);
std::string suffixExpDequeToStr(const std::deque<ExpressionPart> suffix_exp);


#endif
