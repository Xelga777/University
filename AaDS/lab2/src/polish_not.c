#include "polish_not.h"

#include "io.h"
#include "token.h"

int main() {
  int str_length = 0, arr_length = 0;
  char *string = input(&str_length);
  struct token *array = tokens_gen(string, str_length, &arr_length);

  arr_length--;
  free(string);

  if (array && (array = tokens_control(array, arr_length))) {
    struct stack *stack = polish_stack(array, arr_length);
    if (stack) {
      struct stack *top = pop(&stack);
      struct stack *inverted = init(top->data);

      for (struct stack *p = pop(&stack); p != NULL; p = pop(&stack)) {
        inverted = push(inverted, p->data);
        free(p);
      }

      output(inverted);

      destroy(inverted);
      destroy(stack);
      free(array);
    } else {
      printf("Invalid expression u stupid");
    }
  } else {
    printf("Invalid expression u stupid");
  }
}

struct stack *polish_stack(const struct token *array, int length) {
  struct stack *stack = NULL;
  struct stack *out = NULL;
  int flag = 1;

  for (int i = 0; i < length; i++) {
    struct token current_token = array[i];

    if (current_token.type == VAR) {
      out = out != NULL ? push(out, current_token) : init(current_token);
    } else if (SUM <= current_token.type && current_token.type <= DIV) {
      struct token op2;

      while (peek(stack, &op2) && (SUM <= op2.type && op2.type <= DIV) &&
             op2.priority >= current_token.priority) {
        struct stack *buff = pop(&stack);
        out = out != NULL ? push(out, buff->data) : init(buff->data);
        free(buff);
      }

      stack = stack != NULL ? push(stack, current_token) : init(current_token);
    } else if (current_token.type == BRo) {
      stack = stack != NULL ? push(stack, current_token) : init(current_token);
    } else if (current_token.type == BRc) {
      struct token br;

      while (peek(stack, &br) && br.type != BRo) {
        struct stack *buff = pop(&stack);
        out = out != NULL ? push(out, buff->data) : init(buff->data);
        free(buff);
      }

      if (!peek(stack, &br)) {
        destroy(out);
        out = NULL;
        flag = 0;
      } else {
        struct stack *buff = pop(&stack);

        free(buff);
        buff = pop(&stack);
      }
    }
  }

  struct stack *val = NULL;

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
