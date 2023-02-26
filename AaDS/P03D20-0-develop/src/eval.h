#include "error_code.h"
#include "stack.h"

#ifndef SRC_EVAL_H_
#define SRC_EVAL_H_

double do_var(struct token *self, double x, int *flag);

double do_num(struct token *self, double x, int *flag);

double do_sum(struct token *self, double x, int *flag);

double do_sub(struct token *self, double x, int *flag);

double do_usub(struct token *self, double x, int *flag);

double do_mul(struct token *self, double x, int *flag);

double do_div(struct token *self, double x, int *flag);

double do_sin(struct token *self, double x, int *flag);

double do_cos(struct token *self, double x, int *flag);

double do_tan(struct token *self, double x, int *flag);

double do_ctg(struct token *self, double x, int *flag);

double do_sqrt(struct token *self, double x, int *flag);

double do_ln(struct token *self, double x, int *flag);

#endif  // SRC_EVAL_H_
