#ifndef EXPRESSION_CALC_HPP__
#define EXPRESSION_CALC_HPP__

#include <string>

// typedef double (AlphaSymbol_t)();
// typedef double (UnaryOp_t)(double);
typedef double (BinaryOpFunc_t)(double, double);

enum ExpressionPartType {
    NUMBER, OPERATOR
};

struct Symbol {
    int priority;
    BinaryOpFunc_t *func;
};

struct ExpressionPart {
    ExpressionPartType type;
    union {
        double num;
        Symbol op;
    };
};


#endif