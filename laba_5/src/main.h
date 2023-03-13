#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "sorts.h"
#include "additional.h"

#define MAX_INT 10

typedef struct {
    int sort;
    int field;
    int direction;
    char *filename_in;
    char *filename_out; 
} Options;

// funcs
int get_structs(const char *filename, voter **voters, int *voters_count);
int parse_str(int argc, char **argv, Options *options);
int analysing_files(const char* filename_in, const char* filename_out);
int get_structs_num(FILE *fp);
int get_name(char *str, char **name);
void call_sort(Options options, voter *voters, int voters_count);
void output(char *filename, voter *voters, int voters_count);

#endif  // MAIN_H_
