#include <stdio.h>
#include "main.h"
#include "IO.h"

int main() {
    int err_code = 0;
    Matrix matrix = {0, NULL};
    int *vector = NULL;

    err_code = get_size(&matrix);
    
    // TEST OUTPUT:
    // printf("MAT_LEN: %ld\n", matrix.lines_num);
    // for (size_t i = 0; i < matrix.lines_num; i++) {
    //     printf("LINE %ld LEN: %ld\n", i, matrix.p_lines[i].len);
    // }
    
    if (!err_code) err_code = get_data(&matrix);
    if (!err_code) err_code = compling_task(&matrix, &vector);
    if (!err_code) output(&matrix, vector);

    err_handler(&err_code);
    free_data(&matrix, &vector);
    return err_code;
}

// Support functions
void err_handler(int *err_code) {
    switch (*err_code) {
        case -1:
            printf("Произошла внутренняя ошибка, связанная с выделением памяти\n");
            break;
        case 1:
            printf("Введены некорректные данные, введите целочисленное значение\n");
            *err_code = 0;
            break;
        case 2:
            printf("Введено невалидное значение. Количество должно быть целым числом большим 0\n");
            *err_code = 0;
            break;
        default:
            break;
    }
}

void free_data(Matrix *matrix, int **vector) {
    Line *lines = matrix->p_lines;
    for (size_t i = 0; i < matrix->lines_num; i++) {
        if ((lines[i]).data) free((lines[i]).data);
    }
    
    if (lines) free(lines);
    if (*vector) free(*vector);
}
// End support functions

int compling_task(Matrix *matrix, int **vector) {
    int err_code = 0;
    Line *lines = matrix->p_lines;
    
    *vector = (int*)calloc(matrix->lines_num, sizeof(int));
    if (!vector) {
        err_code = -1;
        return err_code;
    }

    for (size_t i = 0; i < matrix->lines_num; i++) {
        if (i != matrix->lines_num - 1) {
            (*vector)[i] = unique_elems(lines[i], lines[i + 1]);    
        } else {
            (*vector)[i] = unique_elems(lines[i], lines[0]);
        }
    }
    
    return err_code;
}

int unique_elems(Line line_0, Line line_1) {
    int diff = line_0.len;

    for (size_t i = 0; i < line_0.len; i++) {
        for (size_t j = 0; j < line_1.len; j++) {
            if (line_0.data[i] == line_1.data[j]) {
                diff -= 1;
                break;
            }
        }
    }
    
    return diff;
}
