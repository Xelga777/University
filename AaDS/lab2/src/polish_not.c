#include "polish_not.h"

#include "io.h"

int main() {
  int str_length = 0, arr_length = 0;
  char *string = input(&str_length);
  struct token *array = tokens_gen(string, str_length, &arr_length);

  arr_length--;
  free(string);

  if (array && (array = tokens_control(array, arr_length))) {
    struct stack *stack = polish_stack(array, arr_length);
    struct stack *p_stack = stack;

    if (stack) {
      struct stack *inverted = invert(stack);
      struct stack *p_inv = inverted;

      output(inverted);

      if (p_inv) destroy(p_inv);
      if (p_stack) destroy(p_stack);
    } else {
      printf("Invalid expression u stupid");
    }

    free(array);
  } else {
    printf("Invalid expression u stupid");
  }
}

struct stack *polish_stack(const struct token *array, int length) {
  struct stack *stack = NULL;
  struct stack *p_stack = stack;
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
      }

      stack = stack != NULL ? push(stack, current_token) : init(current_token),
      p_stack = stack;
    } else if (current_token.type == BRo) {
      stack = stack != NULL ? push(stack, current_token) : init(current_token),
      p_stack = stack;
    } else if (current_token.type == BRc) {
      struct token br;

      while (peek(stack, &br) && br.type != BRo) {
        struct stack *buff = pop(&stack);
        out = out != NULL ? push(out, buff->data) : init(buff->data);
      }

      if (!peek(stack, &br)) {
        if (out) destroy(out);
        out = NULL;
        flag = 0;
      } else {
        pop(&stack);
        pop(&stack);
      }
    }
  }

  struct stack *val = NULL;

  while (flag && (val = pop(&stack)) != NULL) {
    if (val->data.type == BRo) {
      if (out) destroy(out);
      out = NULL;
      break;
    } else {
      out = out != NULL ? push(out, val->data) : init(val->data);
    }
  }
  if (p_stack) destroy(p_stack);
  return out;
}
