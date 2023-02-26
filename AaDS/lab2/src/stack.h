#ifndef STACK_H_
#define STACK_H_

#include "token.h"

// #ifdef __LIST_IMPLEMENTATION__
struct stack {
  struct token data;
  struct stack *prev;
};

struct stack *init(struct token data);

struct stack *push(struct stack *top, struct token data);

struct stack *pop(struct stack **top);

void destroy(struct stack *top);

int peek(struct stack *top, struct token *out);
// #endif  // __LIST_IMPLEMENTATION__

#ifdef __VECTOR_IMPLEMENTATION__

#endif  // __VECTOR_IMPLEMENTATION__

#endif  // STACK_H_
