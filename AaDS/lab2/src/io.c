#include "io.h"

#include "stack.h"

char *input(int *length) {
  *length = 1;
  char *string = calloc(*length, sizeof(char)), element;

  scanf("%c", &element);

  while (element != '\n') {
    if (element != ' ') {
      string[(*length)++ - 1] = element;
      void *tmp = realloc(string, (*length) * sizeof(char));
      if (NULL != tmp) {
        string = tmp;
      }
    }
    scanf("%c", &element);
  }
  --(*length);
  return string;
}

void output(struct stack *polish_stack) {
  struct token el;
  while (peek(polish_stack, &el)) {
  //   switch (el.type) {
  //     case VAR:
  //       printf("%c", el.var_name);
  //       break;
  //     case SUM:
  //       printf("+");
  //       break;
  //     case SUB:
  //       printf("-");
  //       break;
  //     case USUB:
  //       printf("-");
  //       break;
  //     case MUL:
  //       printf("*");
  //       break;
  //     case DIV:
  //       printf("/");
  //       break;
  //     default:
  //       break;
  //   }

  // TESTOUT:
    printf("NUM: %ld\n", polish_stack->num);

    pop(&polish_stack);
  }
}
