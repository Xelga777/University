#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include "token.h"

struct token_stack {
    struct token data;
    struct token_stack *prev;
};

struct token_stack *init(struct token data);

struct token_stack *push(struct token_stack *top, struct token data);

struct token_stack *pop(struct token_stack **top);

void destroy(struct token_stack *top);

int peek(struct token_stack *top, struct token *out);


#endif  // SRC_STACK_H_

