#include "stack.h"

struct token_stack *init(struct token data) {
    struct token_stack *new = (struct token_stack *) malloc(sizeof(struct token_stack));

    new->data = data;
    new->prev = NULL;

    return new;
}

struct token_stack *push(struct token_stack *top, struct token data) {
    struct token_stack *new = init(data);
    new->prev = top;

    return new;
}

struct token_stack *pop(struct token_stack **top) {
    struct token_stack *popped = NULL;
    if (*top != NULL) {
        popped = *top;
        *top = popped->prev;
    }

    return popped;
}

void destroy(struct token_stack *top) {
    if (top != NULL) {
        destroy(top->prev);
    }
    free(top);
}

int peek(struct token_stack *top, struct token *out) {
    int flag = top == NULL;
    if (!flag) {
        *out = top->data;
    }

    return !flag;
}
