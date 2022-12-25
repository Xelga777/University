#ifndef ADDITIONAL_H_
#define ADDITIONAL_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    char polling_n[7];
    int age;
} voter;

void free_structs(voter *voters, int voters_count);
void swap_voters(voter *v1, voter *v2);
void err_handler(int err_code);

#endif  // ADDITIONAL_H_
