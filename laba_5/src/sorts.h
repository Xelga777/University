#ifndef SORTS_H_
#define SORTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define REDUCTION_FACTOR 1.247331

// funcs
int name_compare_direct(const void *v1, const void *v2);
int polling_n_compare_direct(const void *v1, const void *v2);
int age_compare_direct(const void *v1, const void *v2);
int name_compare_reverse(const void *v1, const void *v2);
int polling_n_compare_reverse(const void *v1, const void *v2);
int age_compare_reverse(const void *v1, const void *v2);

void shell_sort(void *voters, int num, int comparator(const void *, const void *));
void comb_sort(void *voters, int num, int comparator(const void *, const void *));
void sortq(void *voters, int num, int comparator(const void *, const void *));

void swap_voters(voter *v1, voter *v2);

#endif  // SORTS_H_
