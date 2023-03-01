#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef __LIST_IMPLEMENTATION__
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
#endif  // __LIST_IMPLEMENTATION__

#ifdef __VECTOR_IMPLEMENTATION__
struct stack *init(struct token data) {
  struct stack *new = (struct stack *)calloc(SIZE, sizeof(struct stack));

  new->data = data;
  new->size = SIZE;
  new->root = 1;

  return new;
}

struct stack *push(struct stack *top, struct token data) {
  if (top->root >= top->size) {
    top->size += SIZE;
    top = realloc(top, top->size * sizeof(struct stack));
  }

  top[top->root].data = data;
  top->root++;

  return top;
}

struct stack *pop(struct stack **top) {
  struct stack *popped = NULL;
  if (*top != NULL) {
    if ((*top)->root == 0) return NULL;

    popped = *top;

    (*top)->root--;
    *top = top[(*top)->root - 1];
  }

  return popped;
}

void destroy(struct stack *top) { free(top); }

int peek(struct stack *top, struct token *out) {
  int flag = top == NULL;
  if (!flag) *out = top->data;
  return !flag;
}

#endif  // __VECTOR_IMPLEMENTATION__
