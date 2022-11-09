#include <stdio.h>
#include <stdlib.h>
#include "computating.h"

int data_computating(int n, int* numerators, int* denomenators, int* len_res, int** result) {
    if (numerators == NULL || denomenators == NULL) return -4;

    // minmax[0] - index of min, minmax[1] - index of max
    int minmax[2] = {0};

    search_minmax(n, numerators, denomenators, minmax);

    // Test output:
    // printf("minInd: %d, maxInd: %d\n", minmax[0], minmax[1]);

    *len_res = computate_sequence(n, numerators, denomenators, result, minmax);
    return 4;
}

void create_res_seqs(int** res_num, int** res_den, int* numers, int* denomers, int* result, int len_res) {
    *res_num = (int*)malloc(len_res * sizeof(int));
    *res_den = (int*)malloc(len_res * sizeof(int));
    int i = 0;

    for (int* p = *res_num; p - *res_num < len_res; p++, i++) *p = numers[result[i]];
    i = 0;
    for (int* p = *res_den; p - *res_den < len_res; p++, i++) *p = denomers[result[i]];
}

void search_minmax(int n, int* numers, int* denomers, int* minmax) {
    for (int i = 0; i < n; i++) {
        if (my_abs(numers[i] * denomers[minmax[0]]) <= my_abs(numers[minmax[0]] * denomers[i])) {
            minmax[0] = i;
        }
        if (my_abs(numers[i] * denomers[minmax[1]]) >= my_abs(numers[minmax[1]] * denomers[i])) {
            minmax[1] = i;
        }
    }
}

int computate_sequence(int n, int* numers, int* denomers, int** result, int* minmax) {
    int len_res = 0;
    int* p = *result;
    // *result = NULL;
    int min_num = numers[minmax[0]];
    int max_num = numers[minmax[1]];
    int min_den = denomers[minmax[0]];
    int max_den = denomers[minmax[1]];

    if (max_num < min_num) swap(&min_num, &max_num);
    if (max_den < min_den) swap(&max_den, &min_den);

    for (int i = 0; i < n; i++) {
        if (numers[i] < max_num && numers[i] > min_num && denomers[i] < max_den && denomers[i] > min_den) {
            len_res += 1;
            *result = (int*)realloc(*result, len_res * sizeof(int));
            p = *result;
            p[len_res - 1] = i;
        }
    }

    // Test output:
    // printf("minNum: %d, maxNum: %d\n", min_num, max_num);
    // printf("minDen: %d, maxDen: %d", min_den, max_den);

    return len_res;
}

void swap(int* a, int* b) {
    int c = *a;
    *a = *b;
    *b = c;
}

int my_abs(int a) {
    if (a >= 0) {
        return a;
    } else {
        return (-a);
    }
}
