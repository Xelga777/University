#ifndef STACK_H_
#define STACK_H_

#define SIZE 10

#include "token.h"

#ifdef __LIST_IMPLEMENTATION__
struct stack {
  struct token data;
  struct stack *prev;
};
#endif  // __LIST_IMPLEMENTATION__

// #ifdef __VECTOR_IMPLEMENTATION__
struct stack {
  struct token data;
  size_t size;
  size_t num;
};
// #endif  // __VECTOR_IMPLEMENTATION__

struct stack *init(struct token data);

struct stack *push(struct stack *top, struct token data);

struct stack *pop(struct stack **top);

void destroy(struct stack *top);

int peek(struct stack *top, struct token *out);
#endif  // STACK_H_
