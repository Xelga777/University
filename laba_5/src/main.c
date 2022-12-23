#include "main.h"

int main(int argc, char **argv) {
    int err_code = 0;
    Options options = {0, 0, 0, NULL, NULL};
    voter *voter = {NULL};

    if (!err_code) err_code = parse_str(argc, argv, &options);
    if (!err_code) err_code = get_structs(options.filename_in, &voter);

    /* code */

    if (err_code) err_handler(err_code);

    if (voter) free(voter);
    return err_code;
}

int parse_str(int argc, char **argv, Options *options) {
    int err_code = 0;
    int opt = 0;

    Options check_duplicates = {0, 0, 0, NULL, NULL};

    if (argc < 5) err_code = -1;

    while (opt != -1) {
        if (err_code) break;

        opt = getopt(argc, argv, "i:o:rdnpacsq");

        if ((opt == 'c' || opt == 's' || opt == 'q') && !check_duplicates.sort) {
            (*options).sort = opt;
            check_duplicates.sort = 1;
        } else if ((opt == 'n' || opt == 'p' || opt == 'a') && !check_duplicates.field) {
            (*options).field = opt;
            check_duplicates.field = 1;
        } else if ((opt == 'r' || opt == 'd') && !check_duplicates.direction) {
            (*options).direction = opt;
            check_duplicates.direction = 1;
        } else if (opt == 'i' && !check_duplicates.filename_in) {
            (*options).filename_in = optarg;
            check_duplicates.filename_in = "1";
        } else if (opt == 'o' && !check_duplicates.filename_out) {
            (*options).filename_out = optarg;
            check_duplicates.filename_out = "1";
        } else if (opt == '?') {
            err_code = -2;
        }
    }

    if (!err_code) err_code = analysing_files((*options).filename_in, (*options).filename_out);

    return err_code;
}

int get_structs(const char *filename, voter **voters) {
    int err_code = 0;

    FILE *fp = fopen(filename, "r");
    FILE *fp_cpy = fp;

    char *line = NULL;
    char age_str[MAX_INT] = {0};
    char ch = 0;
    int str_len = 0, voters_count = 0;

    while (ch != EOF) {
        str_len = 0;

        while (ch != '\n' || ch != EOF) {
            fscanf(fp_cpy, "%*c", &ch);
            str_len += 1;
        }

        line = (char*)malloc((str_len + 1) * sizeof(char));
        fscanf(fp, "%[^\n]*c", line);
        line[str_len] = '\0';

        printf("LINE: %s\n", line);

        voters_count += 1;
        *voters = realloc(*voters, voters_count * sizeof(voter));

        sscanf(line, "%s%s%s", (*voters)->name, (*voters)->polling_n, age_str);
        (*voters)->age = atoi(age_str);
        free(line);
    }

    return err_code;
}

int analysing_files(const char* filename_in, const char* filename_out) {
    int err_code = 0;

    FILE *file_in = fopen(filename_in, "r");
    FILE *file_out = fopen(filename_out, "w");

    if (!file_in || !file_out) err_code = -4;

    return err_code;
}

void err_handler(int err_code) {
    if (err_code == -1) fprintf(stderr, "Too few arguments");
    else if (err_code == -2) fprintf(stderr, "Unknown option");
    else if (err_code == -3) fprintf(stderr, "SMTH");
    else if (err_code == -4) fprintf(stderr, "No such file");
}
