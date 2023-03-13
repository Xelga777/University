#ifndef STATISTICS_H_
#define STATISTICS_H_

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include "sorts.h"
#include "additional.h"

#define NAME_LEN 17

typedef struct {
    int sort;
    int field;
    int direction;
    int elements_num;
    int arrays_num;
} Options;


int parse_str(int argc, char **argv, Options *options);
void call_sort(Options options, voter *voters, int voters_count);

void make_test(Options options);
char *create_name();
void create_polling_n(char polling_n[7]);
int create_age();

#endif  // STATISTICS_H_