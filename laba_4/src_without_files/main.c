#include "main.h"
#include "io.h"

/* This prog handles all strings DURING input

Condition _GNU_VER_ uses funcs from standart lib while
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

    while (source && *source != EOF) {
        #ifdef __GNU_VER__
        if (source) destination = calloc(strlen(source),  50 * sizeof(int));
        #endif

        #ifdef __MY_VER__
        if (source) destination = calloc(my_strlen(source), 50 * sizeof(int));
        #endif
 
        str_processing(source, destination);
        output(source, destination);
        if (source) free(source);
        if (destination) free(destination);

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
        if (*ptr == ' ' || *ptr == '\t') {
            if (!count_delims) *dst = *ptr;
            count_delims += 1;
        } else {
            count_delims = 0;
            *dst = *ptr;
        }
        ptr += 1;
        if (count_delims < 2) dst += 1;
    }

    return err_code;
}

int get_num(char **str, int *len_n) {
    char buf[256];
    char *ptr = *str;
    int number = 0;

    #ifdef __GNU_VER__
    number = atoi(ptr);
    sprintf(buf, "%#x", number);
    *len_n = strlen(buf);
    #endif  // __GNU_VER__

    #ifdef __MY_VER__
    number = my_atoi(ptr);
    sprintf(buf, "%#x", number);
    *len_n = my_strlen(buf);
    #endif  // __MY_VER__

    while ((*ptr >= '0' && *ptr <= '9')
        || (*ptr == '-' && *(ptr + 1) >= '0' && *(ptr + 1) <= '9')) ptr += 1;

    *str = ptr;
    return number;
}
