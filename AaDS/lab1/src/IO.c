#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "IO.h"

int get_size(Matrix *matrix) {
    int err_code = 0;
    int flag = 0;

    // Ввод кол-ва строк
    printf("Введите количество строк матрицы:\n");

    while (!flag) {
        if (!scanf("%ld", &(matrix->lines_num))) {
            err_code = 1;
        } else if (matrix->lines_num <= 0) {
            err_code = 2;
        } else {
            flag = 1;
            matrix->p_lines = (Line*)calloc(matrix->lines_num, sizeof(Line));
        }

        err_handler(&err_code);
        scanf("%*[^\n]");
    }

    Line *lines = matrix->p_lines;

    if (!lines) {
        err_code = -1;
        return err_code;
    }

    // Ввод количества элементов
    for (size_t i = 0; i < matrix->lines_num; i++) {
        flag = 0;
        printf("Введите количество элементов в %ld строке:\n", i);

        while (!flag) {
            if (!scanf("%ld", &(lines[i].len))) {
                err_code = 1;
            } else if (lines[i].len <= 0) {
                err_code = 2;
            } else {
                flag = 1;
                lines[i].data = (int*)calloc(lines[i].len, sizeof(int));

                if (!lines[i].data) {
                    err_code = -1;
                    return err_code;
                }
            }

            err_handler(&err_code);
            scanf("%*[^\n]");
        }
    }

    return err_code;
}

int get_data(Matrix *matrix) {
    int err_code = 0;
    int flag = 0;
    Line *lines = matrix->p_lines;

    for (size_t i = 0; i < matrix->lines_num; i++) {
        printf("Введите значения элементов %ld строки:\n", i);
        for (size_t j = 0; j < lines[i].len; j++) {
            flag = 0;

            while (!flag) {
                if (!scanf("%d", &lines[i].data[j])) {
                    err_code = 1;
                } else {
                    flag = 1;

                }

                err_handler(&err_code);
                scanf("%*[^\n]");
            }
        }
    }

    return err_code;
}

void output(Matrix *matrix, int *vector) {
    printf("Matrix:\n");
    for (size_t i = 0; i < matrix->lines_num; i++) {
        for (size_t j = 0; j < matrix->p_lines[i].len; j++) {
            printf("%d ", matrix->p_lines[i].data[j]);
        }
        printf("\n");
    }

    printf("Vector:\n");
    for (size_t i = 0; i < matrix->lines_num; i++) {
        printf("%d ", vector[i]);
    }
}
