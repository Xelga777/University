#include "main.h"
#include "io.h"
#include "../../../School_21/C2_s21_stringplus-0/src/s21_string.h"
#include <time.h>

/* This prog handles all strings DURING input

Condition _GNU_VER_ uses funcs from standard lib while
Condition _MY_VER_ replaces them with my own implementation */

int main() {
    char *source = NULL;
    char *destination = NULL;

    #ifdef __GNU_VER__
    source = readline(NULL);
    #endif  // __GNU_VER__

    #ifdef __MY_VER__
    my_readline(&source);
    #endif  // __MY_VER__
 
    double time_spent = 0.0;

    while (source && *source != EOF) {
        time_spent = 0.0;
        clock_t begin = clock();

        #ifdef __GNU_VER__
        if (source) destination = calloc(strlen(source),  50 * sizeof(int));
        #endif  // __GNU_VER__

        #ifdef __MY_VER__
        if (source) destination = calloc(my_strlen(source), 50 * sizeof(int));
        #endif  // __MY_VER__
 
        clock_t end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

        str_processing(source, destination);
        output(source, destination);
        if (source) free(source);
        if (destination) free(destination);

        printf("The elapsed time is %f seconds", time_spent);

        #ifdef __GNU_VER__
        source = readline(NULL);
        #endif  // __GNU_VER__

        #ifdef __MY_VER__
        my_readline(&source);
        #endif  // __MY_VER__
    }

    return 0;
}

int str_processing(char *src, char *dst) {
    int err_code = 0;
    int number = 0;
    int count_delims = 0;
    char *ptr = src;
    int len_n = 0;

    if (*src == EOF || src == NULL || dst == NULL) err_code = -2;

    while (*ptr) {
        if (err_code) break;
        if ((*ptr >= '0' && *ptr <= '9') ||
            (*ptr == '-' && *(ptr + 1) >= '0' && *(ptr + 1) <= '9')) {
            count_delims = 0;
            number = get_num(&ptr, &len_n);
            sprintf(dst, "%#x", number);
            dst += len_n;
        }
        if (!*ptr) break;


        if (*ptr == '\t') *ptr = ' ';
        if (*ptr == ' ') {
            // if (!count_delims) *dst = *ptr;
            count_delims += 1;
        } else {
            count_delims = 0;
            // *dst = *ptr;
        }

        if (count_delims > 1) {
            ptr += 1;
        } else {
            *dst = *ptr;
        }
        ptr += 1;
        if (count_delims < 2) dst += 1;
    }

    return err_code;
}

int get_num(char **str, int *len_n) {
    char *buf = calloc(256, sizeof(char));
    char *ptr = *str;
    int number = 0;

    #ifdef __GNU_VER__
    number = atoi(ptr);
    sprintf(buf, "%#x", number);
    *len_n = strlen(buf);
    #endif  // __GNU_VER__

    #ifdef __MY_VER__
    number = my_atoi(ptr);
    s21_sprintf(&buf, "%#x", number);
    *len_n = my_strlen(buf);
    #endif  // __MY_VER__

    while ((*ptr >= '0' && *ptr <= '9')
        || (*ptr == '-' && *(ptr + 1) >= '0' && *(ptr + 1) <= '9')) ptr += 1;

    *str = ptr;
    free(buf);
    return number;
}
