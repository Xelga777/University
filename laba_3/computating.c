#include <stdio.h>
#include <stdlib.h>
#include "analysing_array.h"

int* compare(int n, int* numers, int* denomers) {
    // minmax[0] - index of min, minmax[1] - index of max
    int* minmax = (int*)calloc(2, sizeof(int));
    int comparing_value;

    for (int i = 0; i < n; i++) {
        comparing_value = numers[i];
        for (int j = 0; j < n; j++) {
            if (i != j) comparing_value *= denomers[j];
        }

        if (comparing_value < numers[minmax[0]]) minmax[0] = i;
        if (numers[i] > numers[minmax[1]]) minmax[1] = i;
    }
}