#include "io.h"

int input(FILE *file) {
    file = fopen("source", "w");
    char *line = " ";
    int err_code = 0;

    if (!file) err_code = -2;

    while (line) {
        if (err_code == EOF) break;

        line = readline(NULL);
        if (line == NULL) {
            break;
        } else {
            err_code = fputs(line, file);
            fputc('\n', file);
        }
        free(line);
    }

    if (line) free(line);
    fclose(file);
    return err_code;
}

void output() {
    FILE *src = fopen("source", "r");
    FILE *dst = fopen("computed", "r");
    char *line = NULL;
    size_t len_l = 0;
    int num_str = 0;

    while (getline(&line, &len_l, src) != -1) {
        num_str += 1;
        printf("\nLine number: %d\n", num_str);

        line[strlen(line) - 1] = 0;
        printf("Original: \"%s\"\n", line);

        
        getline(&line, &len_l, dst);
        line[strlen(line) - 1] = 0;
        printf("Computed: \"%s\"", line);
    }

    free(line);
    fclose(src);
    fclose(dst);
}
