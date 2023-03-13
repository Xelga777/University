#include "token.h"

double my_pow(int num);

struct token *tokens_gen(const char *string, int str_length, int *length) {
  struct token *array = malloc(++(*length) * sizeof(struct token));
  for (int i = 0, ind = 0; i < str_length; ind++) {
    char current_el = *(string + i++);
    if (('a' <= current_el && current_el <= 'z') ||
        ('A' <= current_el && current_el <= 'Z')) {
      array[ind].type = VAR;
      array[ind].var_name = current_el;
    } else if (current_el == '+') {
      array[ind].type = SUM;
      array[ind].priority = 0;
    } else if (current_el == '-') {
      array[ind].type = SUB;
      array[ind].priority = 0;
    } else if (current_el == '*') {
      array[ind].type = MUL;
      array[ind].priority = 1;
    } else if (current_el == '/') {
      array[ind].type = DIV;
      array[ind].priority = 1;
    } else if (current_el == '(') {
      array[ind].type = BRo;
    } else if (current_el == ')') {
      array[ind].type = BRc;
    } else {
      free(array);
      array = NULL;
      break;
    }

    void *tmp = realloc(array, ++(*length) * sizeof(struct token));

    if (NULL != tmp) array = tmp;
  }
  return array;
}

struct token *tokens_control(struct token *array, int length) {
  for (int i = 0; i < length; i++) {
    if (array[i].type == SUB &&
        (i == 0 || array[i - 1].type == SUM || array[i - 1].type == SUB ||
         array[i - 1].type == MUL || array[i - 1].type == DIV ||
         array[i - 1].type == BRo)) {
      array[i].type = USUB;
      array[i].priority = 2;
    }
  }

  for (int i = 1; i < length; i++) {
    if (((SUM <= array[i - 1].type && array[i - 1].type <= DIV) &&
         (SUM <= array[i].type && array[i].type <= DIV) &&
         array[i].type != USUB) ||
        (array[i - 1].type == BRo && SUM <= array[i].type &&
         array[i].type <= DIV && array[i].type != USUB) ||
        (SUM <= array[i - 1].type && array[i - 1].type <= DIV &&
         array[i].type == BRc) ||
        (array[i - 1].type == BRo && array[i].type == BRc)) {
      free(array);
      array = NULL;
      break;
    }
  }

  if (array &&
      (!(array[0].type == USUB || array[0].type == VAR ||
         array[0].type == BRo) ||
       !(array[length - 1].type == VAR || array[length - 1].type == BRc))) {
    free(array);
    array = NULL;
  }

  return array;
}

double my_pow(int num) {
  double result = 1;
  if (num == 0) {
    result = 1;
  } else if (num > 0) {
    for (int i = 1; i <= num; i++) result *= 10;
  } else {
    for (int i = num; i < 0; i++) result /= 10;
  }
  return result;
}
