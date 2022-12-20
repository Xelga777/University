#ifndef MAIN_H_
#define MAIN_H_

#include "node.h"
#include <stdio.h>
#include <stdlib.h>

#define CONSONANTS_NUM 20
#define UPPER_TO_LOW 32

node *getstr(int *final, char c);
void delete_consonants(node *string);
void output(node *string);


#endif  // MAIN_H_