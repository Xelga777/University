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
    int count = 0;
    for (int i = 0; i < (int)strlen(line); i++) {
        if (line[i] == ' ') count += 1;
    }

    if (count == 4) {
        return 0;
    } else {
        return -3;
    }
}

int analizing_polling_n(char str[7]) {
    int err_code = 0;
    for (int i = 0; i < 7; i++) {
        if (i < 3 && !((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))) {
            err_code = -3;
        } else if (i == 3 && str[i] != '-') {
            err_code = -3;
        } else if (i > 4 && (str[i] < '0' || str[i] > '9')) {
            err_code = -3;
        }
    }
    return err_code;
}

void err_handler(int err_code) {
    if (err_code == -1) fprintf(stderr, "Too few arguments");
    else if (err_code == -2) fprintf(stderr, "Unknown option");
    else if (err_code == -3) fprintf(stderr, "Incorrect data");
    else if (err_code == -4) fprintf(stderr, "No such file");
}
