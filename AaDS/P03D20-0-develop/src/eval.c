#include "eval.h"
#include <math.h>

#define ignore(expr) ((void) expr)

double do_var(struct token *self, double x, int *flag) {
    ignore(self);
    ignore(flag);

    return x;
}

double do_num(struct token *self, double x, int *flag) {
    ignore(x);
    ignore(flag);

    return self->value;
}

double do_sum(struct token *self, double x, int *flag) {
    return (*self->leftPtr->eval)(self->leftPtr, x, flag) +
           (*self->rightPtr->eval)(self->rightPtr, x, flag);
}

double do_sub(struct token *self, double x, int *flag) {
    return (*self->leftPtr->eval)(self->leftPtr, x, flag) -
           (*self->rightPtr->eval)(self->rightPtr, x, flag);
}

double do_usub(struct token *self, double x, int *flag) {
    /**
     * only right branch of the tree is evaluated
     * if it happens to be unary operator (function)
     */
    return -(*self->rightPtr->eval)(self->rightPtr, x, flag);
}

double do_mul(struct token *self, double x, int *flag) {
    return (*self->leftPtr->eval)(self->leftPtr, x, flag) *
           (*self->rightPtr->eval)(self->rightPtr, x, flag);
}

double do_div(struct token *self, double x, int *flag) {
    double left = (*self->leftPtr->eval)(self->leftPtr, x, flag);
    double right = (*self->rightPtr->eval)(self->rightPtr, x, flag);

    if (right == 0) { /* division by zero */
        *flag = ERR_DIV;
        right = 1;
    }

    return left / right;
}

double do_sin(struct token *self, double x, int *flag) {
    /**
     * only right branch of the tree is evaluated
     * if it happens to be unary operator (function)
     */
    return sin((*self->rightPtr->eval)(self->rightPtr, x, flag));
}

double do_cos(struct token *self, double x, int *flag) {
    /**
     * only right branch of the tree is evaluated
     * if it happens to be unary operator (function)
     */
    return cos((*self->rightPtr->eval)(self->rightPtr, x, flag));
}

double do_tan(struct token *self, double x, int *flag) {
    /**
     * only right branch of the tree is evaluated
     * if it happens to be unary operator (function)
     */
    double arg = (*self->rightPtr->eval)(self->rightPtr, x, flag);
    if (cos(arg) == 0) {
        *flag = ERR_DIV;
        arg = 1;
    }

    return tan(arg);
}

double do_ctg(struct token *self, double x, int *flag) {
    /**
     * only right branch of the tree is evaluated
     * if it happens to be unary operator (function)
     */
    double arg = (*self->rightPtr->eval)(self->rightPtr, x, flag);
    if (sin(arg) == 0) {
        *flag = ERR_DIV;
        arg = 1;
    }

    return cos(arg) / sin(arg);
}

double do_sqrt(struct token *self, double x, int *flag) {
    /**
     * only right branch of the tree is evaluated
     * if it happens to be unary operator (function)
     */
    double arg = (*self->rightPtr->eval)(self->rightPtr, x, flag);
    if (arg < 0) { /* sqrt of negative number */
        *flag = ERR_SQRT;
        arg = 1;
    }

    return sqrt(arg);
}

double do_ln(struct token *self, double x, int *flag) {
    /**
     * only right branch of the tree is evaluated
     * if it happens to be unary operator (function)
     */
    double arg = (*self->rightPtr->eval)(self->rightPtr, x, flag);
    if (arg <= 0) { /* logarithmic error */
        *flag = ERR_LOG;
        arg = 1;
    }
    return log(arg);
}
