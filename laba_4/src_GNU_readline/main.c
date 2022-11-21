#include "main.h"
#include "io.h"

// This prog handles all strings AFTER input, not in process/
int main() {
    int err_code = 1;
    FILE *source = NULL;
    FILE *destination = NULL;
    
    err_code = input(source);
    err_code = file_processing(source, destination);
    output();

    return err_code;
}

int file_processing(FILE *src, FILE *dst) {
    src = fopen("source", "r");
    dst = fopen("computed", "w");

    int err_code = 0;
    char *line = NULL;
    size_t len_line = 0;
    int number = 0;
    int count_delims = 0;

    if (src == NULL || dst == NULL) err_code = -2;
    
    while (getline(&line, &len_line, src) != -1) {
        char *ptr = line;

        while (*ptr) {
            if ((*ptr >= '0' && *ptr <= '9') || (*ptr == '-' && *(ptr + 1) >= '0' && *(ptr + 1) <= '9' )) {
                number = get_num(&ptr);
                fprintf(dst, "%#x", number);
            }
            if (*ptr == ' ' || *ptr == '\t') {
                count_delims ? : putc(*ptr, dst);
                count_delims += 1;
            } else {
                count_delims = 0;
                putc(*ptr, dst);
            }
            ptr += 1;
        }
    }

    if (line) free(line);
    if (src) fclose(src);
    if (dst) fclose(dst);
    return err_code;
}

int get_num(char **ptr) {
    int number = 0;
    number = atoi(*ptr);

    while ((**ptr >= '0' && **ptr <= '9') || (**ptr == '-' && **(ptr + 1) >= '0' &&
            **(ptr + 1) <= '9' )) {
        *ptr += 1;
    }

    return number;
}
