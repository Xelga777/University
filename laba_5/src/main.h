#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "sorts.h"

#define MAX_INT 10

typedef struct {
    int sort;
    int field;
    int direction;
    char *filename_in;
    char *filename_out; 
} Options;

typedef struct {
    char *name;
    char polling_n[7];
    int age;
} voter;


// funcs
int parse_str(int argc, char **argv, Options *options);
int get_structs(const char *filename, voter **voters);
int analysing_files(const char* filename_in, const char* filename_out);
void err_handler(int err_code);

#endif  // MAIN_H_
