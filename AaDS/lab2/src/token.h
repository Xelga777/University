#ifndef TOKEN_H_
#define TOKEN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum types { VAR, SUM, SUB, USUB, MUL, DIV, BRo, BRc };

struct token {
  enum types type;
  char var_name;
  int priority;
};

struct token *tokens_gen(const char *string, int str_length, int *length);
struct token *tokens_control(struct token *array, int length);

#endif  // TOKEN_H_
