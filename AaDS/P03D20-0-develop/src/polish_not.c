#include "polish_not.h"

struct token_stack *polish_stack(const struct token *array, int length) {
    struct token_stack *stack = NULL;
    struct token_stack *out = NULL;
    int flag = 1;

    for (int i = 0; i < length; i++) {
        struct token current_token = array[i];

        if (current_token.type == NUM || current_token.type == VAR) {
            out = out != NULL ? push(out, current_token) : init(current_token);
        } else if (SIN <= current_token.type && current_token.type <= LN) {
            stack = stack != NULL ? push(stack, current_token) : init(current_token);
        } else if (SUM <= current_token.type && current_token.type <= DIV) {
            struct token op2;

            while (peek(stack, &op2) && (SUM <= op2.type && op2.type <= DIV)
                && op2.priority >= current_token.priority) {
                struct token_stack *buff = pop(&stack);
                out = out != NULL ? push(out, buff->data) : init(buff->data);
                free(buff);
            }

            stack = stack != NULL ? push(stack, current_token) : init(current_token);
        } else if (current_token.type == BRo) {
            stack = stack != NULL ? push(stack, current_token) : init(current_token);
        } else if (current_token.type == BRc) {
            struct token br;

            while (peek(stack, &br) && br.type != BRo) {
                struct token_stack *buff = pop(&stack);
                out = out != NULL ? push(out, buff->data) : init(buff->data);
                free(buff);
            }

            if (!peek(stack, &br)) {
                destroy(out);
                out = NULL;
                flag = 0;
            } else {
                struct token_stack *buff = pop(&stack);

                free(buff);
                buff = pop(&stack);

                if (SIN <= buff->data.type && buff->data.type <= LN) {
                    out = out != NULL ? push(out, buff->data) : init(buff->data);
                }
                free(buff);
            }
        }
    }

    struct token_stack *val;
    
    while (flag && (val = pop(&stack)) != NULL) {
        if (val->data.type == BRo) {
            destroy(out);
            out = NULL;
            free(val);
            break;
        } else {
            out = out != NULL ? push(out, val->data) : init(val->data);
            free(val);
        }
    }
    destroy(stack);
    return out;
}
