#include "modio.h"
#include "token.h"
#include "stack.h"
#include "polish_not.h"
#include "eval.h"


int main() {
    int str_length = 0, arr_length = 0/*, matrix[N][M] */ ;
    char *string = input(&str_length);
    struct token *array = tokens_gen(string, str_length, &arr_length);

    arr_length--;
    free(string);

    if (array != NULL && (array = tokens_control(array, arr_length))) {
        struct token_stack *stack = polish_stack(array, arr_length);

        if (stack != NULL) {
            struct token_stack *top = pop(&stack);
            struct token_stack *inverted = init(top->data);

            for (struct token_stack *p = pop(&stack); p != NULL; p = pop(&stack)) {
                inverted = push(inverted, p->data);
                free(p);
            }

            struct token_stack *result = NULL;
            for (struct token_stack *p = pop(&inverted); p != NULL; p = pop(&inverted)) {
                switch (p->data.type) {
                    case VAR: {
                        p->data.eval = &do_var;
                        result = result == NULL ? init(p->data) : push(result, p->data);
                        break;
                    }

                    case NUM: {
                        p->data.eval = &do_num;
                        result = result == NULL ? init(p->data) : push(result, p->data);
                        break;
                    }

                    case SUM: {
                        p->data.eval = &do_sum;
                        struct token_stack *left = pop(&result);
                        struct token_stack *right = pop(&result);
                        p->data.leftPtr = &right->data;
                        p->data.rightPtr = &left->data;

                        result = result == NULL ? init(p->data) : push(result, p->data);
                        break;
                    }

                    case SUB: {
                        p->data.eval = &do_sub;
                        struct token_stack *left = pop(&result);
                        struct token_stack *right = pop(&result);
                        p->data.leftPtr = &right->data;
                        p->data.rightPtr = &left->data;

                        result = result == NULL ? init(p->data) : push(result, p->data);
                        break;
                    }

                    case USUB: {
                        p->data.eval = &do_usub;
                        struct token_stack *right = pop(&result);
                        p->data.rightPtr = &right->data;

                        result = result == NULL ? init(p->data) : push(result, p->data);
                        break;
                    }

                    case MUL: {
                        p->data.eval = &do_mul;
                        struct token_stack *left = pop(&result);
                        struct token_stack *right = pop(&result);
                        p->data.leftPtr = &right->data;
                        p->data.rightPtr = &left->data;

                        result = result == NULL ? init(p->data) : push(result, p->data);
                        break;
                    }

                    case DIV: {
                        p->data.eval = &do_div;
                        struct token_stack *left = pop(&result);
                        struct token_stack *right = pop(&result);
                        p->data.leftPtr = &right->data;
                        p->data.rightPtr = &left->data;

                        result = result == NULL ? init(p->data) : push(result, p->data);
                        break;
                    }

                    case SIN: {
                        p->data.eval = &do_sin;
                        struct token_stack *right = pop(&result);
                        p->data.rightPtr = &right->data;
                        result = result == NULL ? init(p->data) : push(result, p->data);
                        break;
                    }

                    case COS: {
                        p->data.eval = &do_cos;
                        struct token_stack *right = pop(&result);
                        p->data.rightPtr = &right->data;
                        result = result == NULL ? init(p->data) : push(result, p->data);
                        break;
                    }

                    case TAN: {
                        p->data.eval = &do_tan;
                        struct token_stack *right = pop(&result);
                        p->data.rightPtr = &right->data;
                        result = result == NULL ? init(p->data) : push(result, p->data);
                        break;
                    }

                    case CTG: {
                        p->data.eval = &do_ctg;
                        struct token_stack *right = pop(&result);
                        p->data.rightPtr = &right->data;
                        result = result == NULL ? init(p->data) : push(result, p->data);
                        break;
                    }

                    case SQRT: {
                        p->data.eval = &do_sqrt;
                        struct token_stack *right = pop(&result);
                        p->data.rightPtr = &right->data;
                        result = result == NULL ? init(p->data) : push(result, p->data);
                        break;
                    }

                    case LN: {
                        p->data.eval = &do_ln;
                        struct token_stack *right = pop(&result);
                        p->data.rightPtr = &right->data;
                        result = result == NULL ? init(p->data) : push(result, p->data);
                        break;
                    }

                    default: break;
                }
                free(p);
            }

            output(&result->data);

            destroy(inverted);
            destroy(result);
            destroy(stack);
            destroy(top);
            free(array);
        } else {
            printf("Invalid Expression");
        }
    } else {
        printf("Invalid Expression");
    }
    return 0;
}
