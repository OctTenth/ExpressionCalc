#ifndef EXPRESSION_CALC_HPP__
#define EXPRESSION_CALC_HPP__

#include <string>
#include <map>
#include <cmath>

// typedef double (AlphaSymbol_t)();
// typedef double (UnaryOp_t)(double);
typedef double (BinaryOpFunc_t)(double, double);

typedef std::map<std::string, Symbol> mathSymbolMap_t;

enum ExpressionPartType {
    NUMBER, OPERATOR
};

struct Symbol {
    int priority;
    BinaryOpFunc_t *func_p;
};

struct ExpressionPart {
    ExpressionPartType type;
    union {
        double num;
        Symbol op;
    };
};


#endif