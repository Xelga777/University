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

struct stack *invert(struct stack *stack) {
  struct stack *top = pop(&stack);
  struct stack *inverted = init(top->data);

  for (struct stack *p = pop(&stack); p != NULL; p = pop(&stack)) {
    inverted = push(inverted, p->data);
  }
  return inverted;
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

  new->size = SIZE;
  new->num = 1;
  new->data = data;

  return new;
}

struct stack *push(struct stack *top, struct token data) {
  if (top->num >= top->size) {
    top->size += SIZE;
    top = realloc(top, top->size * sizeof(struct stack));
  }

  struct stack *p_top = top;
  top++;

  top->num = p_top->num + 1;
  top->data = data;
  top->size = p_top->size;

  return top;
}

struct stack *pop(struct stack **top) {
  struct stack *popped = NULL;
  struct stack *p_top = *top;

  if (p_top != NULL) {
    if (!p_top->num) return NULL;
    popped = *top;

    if (p_top->num != 1) {
      (*top)--;
      (*top)->size = p_top->size;
    } else {
      (*top)->num -= 1;
    }
  }

  return popped;
}

struct stack *invert(struct stack *stack) {
  struct stack *top = pop(&stack);
  struct stack *inverted = init(top->data);

  int i = 2;

  for (struct stack *p = pop(&stack); p != NULL; i++, p = pop(&stack)) {
    inverted = push(inverted, p->data);
    inverted->num = i;
  }
  return inverted;
}

void destroy(struct stack *top) {
  while (pop(&top))
    ;
  free(top);
}

int peek(struct stack *top, struct token *out) {
  int flag = top == NULL;
  if (!flag) *out = top->data;

  return !flag;
}

#endif  // __VECTOR_IMPLEMENTATION__
