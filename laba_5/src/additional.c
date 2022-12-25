#include "additional.h"

void swap_voters(voter *v1, voter *v2) {
    voter tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}

void free_structs(voter *voters, int voters_count) {
    while (voters_count) {
        free((voters[voters_count - 1]).name);
        voters_count -= 1;
    }
    free(voters);
}

void err_handler(int err_code) {
    if (err_code == -1) fprintf(stderr, "Too few arguments");
    else if (err_code == -2) fprintf(stderr, "Unknown option");
    else if (err_code == -3) fprintf(stderr, "SMTH");
    else if (err_code == -4) fprintf(stderr, "No such file");
}
