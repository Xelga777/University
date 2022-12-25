#include "additional.h"

void swap_voters(voter *v1, voter *v2) {
    voter tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}

void free_structs(voter *voters, int voters_count) {
    for (int i = 0; i < voters_count; i++) {
        if ((voters[i]).name) {
            free((voters[i]).name);
        }
    }
    if (voters) free(voters);
}

int analizing_line(char *line) {
    char ch = 0;
    int count = 0;

    for (int i = 0; i < (int)strlen(line); i++) {
        sscanf(line, "%c", &ch);
        if (ch == ' ') count += 1;
        line += 1;
    }
    printf("COUNT: %d\n", count);
    if (count == 4) {
        return 0;
    } else {
        return -3;
    }
}

void err_handler(int err_code) {
    if (err_code == -1) fprintf(stderr, "Too few arguments");
    else if (err_code == -2) fprintf(stderr, "Unknown option");
    else if (err_code == -3) fprintf(stderr, "Incorrect data");
    else if (err_code == -4) fprintf(stderr, "No such file");
}
