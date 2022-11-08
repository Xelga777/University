#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "analysing_array.h"
#include "computating.h"

int main() {
    // Initializing variables
    int chooser = 0;
    int code_result = 0;
    int n = -1;
    int n_res = -1;
    int* numerators = NULL;
    int* denomenators = NULL;
    int* result = NULL;

    while (chooser != 6) {
        if (!chooser) {
            display_menu(chooser);
            display_result(code_result);
            menu(&chooser);
        } else if (chooser == 1) {
            code_result = input(&n, &numerators, &denomenators);
            chooser = 0;
        } else if (chooser == 2) {
            if (insert(&n, &numerators, &denomenators) == -2) {
                code_result = -2;
            } else {
                code_result = 2;
            }
            chooser = 0;
        } else if (chooser == 3) {
            code_result = delete_el(&n, &numerators, &denomenators);
            chooser = 0;
        } else if (chooser == 4) {
            code_result = data_computating(n, numerators, denomenators, &n_res, &result);
            chooser = 0;
        } else if (chooser == 5) {
            output(n, numerators, denomenators, n_res, result);
            code_result = 0;
            chooser = 0;
        }
    }

    free(numerators);
    free(denomenators);
    free(result);

    return 0;
}

int input(int* n, int** numerators, int** denomenators) {
    int correct_input = false;
    int has_input_a = 0;
    display_menu(1);
    printf("\nEnter the length of the original sequences:\n");

    while (!correct_input) {
        if (!scanf("%d", n) || *n < 1) {
            display_menu(1);
            printf("Incorrect length\nTry again\n");
        } else {
            if (*numerators != NULL) free(*numerators);
            if (*denomenators != NULL) free(*denomenators);
            *numerators = (int*)malloc(*n * sizeof(int));
            *denomenators = (int*)malloc(*n * sizeof(int));

            printf("\nEnter the array of numerators:\n");
            while (!has_input_a) has_input_a = initializing_array(*n, *numerators, 0);
            has_input_a = false;

            printf("\nEnter the array of denumenators:\n");
            while (!has_input_a) has_input_a = initializing_array(*n, *denomenators, 1);
            correct_input = true;
        }
    }
    if (numerators == NULL || denomenators == NULL) {
        return -1;
    } else {
        return 1;
    }
}

int initializing_array(int n, int* a, int who) {
    scanf("%*[^\n]");
    int error_flag = -1;
    for (int* p = a; p - a < n; p++) {
        if (!error_flag) break;
        if (!scanf("%d", p) || (who && *p == 0)) {
            printf("\nIncorrect values\nTry again\n");
            error_flag = 0;
        }
    }
    return error_flag;
}

int insert(int *n, int** numerators, int** denomenators) {
    int index, value, buffer, flag = 0;
    printf("\nEnter an index to insert new values:\n");

    while (!flag) {
        if (*numerators == NULL || *denomenators == NULL) return -2;
        if (!scanf("%d", &index) || index < 0 || index > *n) {
            scanf("%*[^\n]");
            printf("\nIncorrect index\nTry again\n");
        } else {
            *n += 1;
            *numerators = (int*)realloc(*numerators, *n * sizeof(int));
            *denomenators = (int*)realloc(*denomenators, *n * sizeof(int));
            printf("\nEnter value to insert in sequence of numerators\n");

            while (!scanf("%d", &value)) {
                scanf("%*[^\n]");
                printf("Incorrect value to insert\nTry again\n");
            }

            for (int* p = *numerators; p - *numerators < *n; p++) {
                if (p - *numerators == index) {
                    buffer = *p;
                    *p = value;
                } else if (p - *numerators > index) {
                    value = *p;
                    *p = buffer;
                    buffer = value;
                }
            }

            printf("\nEnter value to insert in sequence of denomenators\n");
            while (!scanf("%d", &value) || value == 0) {
                scanf("%*[^\n]");
                printf("Incorrect value to insert\nTry again\n");
            }

            for (int* p = *denomenators; p - *denomenators < *n; p++) {
                if (p - *denomenators == index) {
                    buffer = *p;
                    *p = value;
                } else if (p - *denomenators > index) {
                    value = *p;
                    *p = buffer;
                    buffer = value;
                }
            }
            flag = 1;
        }
    }
    return *n;
}

int delete_el(int* n, int** numerators, int** denomenators) {
    int index, flag = 0;
    printf("\nEnter an index to delete elements\n");

    while (!flag) {
        if (*numerators == NULL || *denomenators == NULL) return -3;
        if (!scanf("%d", &index) || (index < 0) || (index >= *n)) {
            scanf("%*[^\n]");
            printf("\nIncorrect index\nTry again\n");
        } else {
            int* buff1 = (int*)malloc((*n - 1) * sizeof(int));
            int* buff2 = (int*)malloc((*n - 1) * sizeof(int));
            int f = 0;
            int* buff = *numerators;

            for (int* p = buff1; p - buff1 < *n - 1; p++) {
                if (p - buff1 == index && !f) {
                    p--;
                    f = 1;
                    continue;
                }
                *p = **numerators;
                *numerators += 1;
            }
            free(buff);
            *numerators = buff1;
            buff = *denomenators;

            for (int* p = buff2; p - buff2 < *n - 1; p++) {
                if (p - buff2 == index && f) {
                    p--;
                    f = 0;
                    continue;
                }
                *p = **denomenators;
                *denomenators += 1;
            }
            free(buff);
            *denomenators = buff2;
            *n -= 1;
        }
        flag = 1;
    }
    return 3;
}

void output(int n_or, int* numer, int* denom, int n_res, int* result) {
    char quit;
    printf("\nSequence of numerators: ");
    if (numer == NULL) {
        printf("NOT INITIALIZED");
    } else {
        for (int* p = numer; p - numer < n_or; p++) {
            printf("%d ", *p);
        }
    }
    printf("\nSequence of denomenators: ");
    if (denom == NULL) {
        printf("NOT INITIALIZED");
    } else {
        for (int* p = denom; p - denom < n_or; p++) printf("%d ", *p);
    }

    printf("\nComputed sequence:\n");
    if (result == NULL) {
        printf("NOT COMPUTED YET");
    } else {
        for (int* p = result; p - result < n_res; p++) printf("%d ", numer[*p]);
        printf("\n");
        for (int i = 0; i < n_res; i++) printf("-; ");
        printf("\n");
        for (int* p = result; p - result < n_res; p++) printf("%d ", denom[*p]);
    }
    printf("\nTo exit mode enter 'q'\n");
    while (quit != 'q') scanf("%c", &quit);
}
