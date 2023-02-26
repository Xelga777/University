#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

// #ifdef __LIST_IMPLEMENTATION__
struct stack *init(struct token data) {
  struct stack *new = (struct stack *)malloc(sizeof(struct stack));

  new->data = data;
  new->prev = NULL;

  return new;
}

struct stack *push(struct stack *top, struct token data) {
  struct stack *new = init(data);
  new->prev = top;

  return new;
}

struct stack *pop(struct stack **top) {
  struct stack *popped = NULL;
  if (*top != NULL) {
    popped = *top;
    *top = popped->prev;
  }

  return popped;
}

void destroy(struct stack *top) {
  if (top != NULL) destroy(top->prev);
  free(top);
}

int peek(struct stack *top, struct token *out) {
  int flag = top == NULL;
  if (!flag) *out = top->data;
  return !flag;
}
// #endif  // __LIST_IMPLEMENTATION__

#ifdef __VECTOR_IMPLEMENTATION__

#endif  // __VECTOR_IMPLEMENTATION__
