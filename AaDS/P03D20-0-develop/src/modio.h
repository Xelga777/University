#ifndef SRC_MODIO_H_
#define SRC_MODIO_H_

#define HEIGHT 25
#define WIDTH 80
#define W_AMP (4 * M_PI)
#define EMPTY_C '.'
#define NON_EMPTY_C '*'
#define ACCURANCY 0.04


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "token.h"
#include "error_code.h"

char *input(int *length);
void output(struct token *root);

#endif  // SRC_MODIO_H_

