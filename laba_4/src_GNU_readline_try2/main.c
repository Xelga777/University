#include "main.h"
#include "io.h"

// This prog handles all strings DURING input
int main() {
    char *source = readline(NULL);
    char *destination;

    while (source && *source != EOF) {
        if (source) destination = calloc(strlen(source),  50 * sizeof(int));
        str_processing(source, destination);
        if (*source != EOF && source != NULL) output(source, destination);
        if (source) free(source);
        if (destination) free(destination);
        source = readline(NULL);
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
        if ((*ptr >= '0' && *ptr <= '9') || (*ptr == '-' && *(ptr + 1) >= '0' && *(ptr + 1) <= '9')) {
            number = get_num(&ptr, &len_n);
            sprintf(dst, "%#x", number);
            dst += len_n;
        }
        if (*ptr == ' ' || *ptr == '\t') {
            if (!count_delims) *dst = *ptr;
            count_delims += 1;
        } else {
            count_delims = 0;
            *dst = *ptr;
        }
        ptr += 1;
        dst += 1;
    }

    return err_code;
}

int get_num(char **ptr, int *len_n) {
    *len_n = 1;
    int number = 0;
    number = atoi(*ptr);

    while ((**ptr >= '0' && **ptr <= '9') || (**ptr == '-' && **(ptr + 1) >= '0' &&
            **(ptr + 1) <= '9')) {
        *ptr += 1;
        *len_n += 1;
    }

    *ptr -= 1;
    return number;
}
