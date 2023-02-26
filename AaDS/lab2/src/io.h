#ifndef IO_H_
#define IO_H_

#include "stack.h"
#include "token.h"

char *input(int *length);
void output(struct stack *polish_stack);

#endif  // IO_H_
