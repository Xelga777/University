#ifndef SRC_TOKEN_H_
#define SRC_TOKEN_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum types {
    VAR = 0,
    NUM = 1,
    SUM = 2,
    SUB = 3,
    USUB = 4,
    MUL = 5,
    DIV = 6,
    BRo = 7,
    BRc = 8,
    SIN = 9,
    COS = 10,
    TAN = 11,
    CTG = 12,
    SQRT = 13,
    LN = 14
};


struct token {
    enum types type;
    int priority;
    double value;
    struct token* leftPtr;
    struct token* rightPtr;
    double (*eval)(struct token *self, double x, int *flag);
};

struct token *tokens_gen(const char *string, int str_length, int *length);
struct token *tokens_control(struct token *array, int length);

#endif  // SRC_TOKEN_H_
