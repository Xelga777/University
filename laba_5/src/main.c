#include "main.h"

int main(int argc, char **argv) {
    int err_code = 0;
    Options options = {0, 0, 0, NULL, NULL};
    voter *voter = {NULL};

    /* if (!err_code) err_code = parse_str(argc, argv, &options);
    if (!err_code) err_code = get_structs(options.filename_in, &voter);

    if (err_code) err_handler(err_code);

    if (voter) free(voter); */

    // TEST get_name:
    char line[100] = {"NAME SONAME sss XXX-321 19"};
    char *name = malloc(1000);
    name = get_name(line);
    printf("NAME: %s", name);

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
    FILE *fp_cpy = fopen(filename, "r");

    char *line = NULL;
    char age_str[MAX_INT] = {0};
    char ch = 0;
    int str_len = 0, voters_count = 0;


    while (!feof(fp)) {
        str_len = 0;

        do {
            fscanf(fp_cpy, "%c", &ch);
            str_len += 1;
        } while (ch != '\n' && !feof(fp_cpy));
        
        line = (char*)malloc((str_len + 1) * sizeof(char));
        fscanf(fp, "%[^\n]", line);
        fscanf(fp, "%*c");
        line[str_len] = '\0';

        // TEST OUT:
        // printf("LINE: %s\n", line);

        voters_count += 1;
        *voters = realloc(*voters, voters_count * sizeof(voter));

        // TEST
        // (*voters)->name = malloc(999 * sizeof(char));

        // sscanf(line, "%[-^\n]", (*voters)->name);
        // sscanf(line, "%s%s",(*voters)->polling_n, age_str);

        // strcat((*voters)->name, name);
        (*voters)->age = atoi(age_str);
        // voters++;

        // TEST OUT:
        // printf("NAME: %s\nPOLLING_N: %s\nAGE: %d\n\n", (*voters)->name, (*voters)->polling_n, (*voters)->age);
        // free((*voters)->name);
        free(line);
    }

    fclose(fp);
    fclose(fp_cpy);
    return err_code;
}

int analysing_files(const char* filename_in, const char* filename_out) {
    int err_code = 0;

    FILE *file_in = fopen(filename_in, "r");
    FILE *file_out = fopen(filename_out, "w");

    if (!file_in || !file_out) err_code = -4;

    if (file_in) fclose(file_in);
    if (file_out) fclose(file_out);

    return err_code;
}

// int analysing_structs(voter *voters) {

// }
char *get_name(char *str) {
    int len = 0, count_sp = 0;
    char *name = malloc(sizeof(char));

    
    while (name[len] && count_sp < 3) {
        sscanf(str, "%c", &name[len]);
        len += 1;
        name = (char*)realloc(name, len);
        if (name[len] == ' ') count_sp += 1;
    }
    // name[len] = '\0';
    printf("NAME IN FUNC: %s\n", name);

    if (name[len] == -1) {
        return 0;
    } else {
        return name;
    }
}

void err_handler(int err_code) {
    if (err_code == -1) fprintf(stderr, "Too few arguments");
    else if (err_code == -2) fprintf(stderr, "Unknown option");
    else if (err_code == -3) fprintf(stderr, "SMTH");
    else if (err_code == -4) fprintf(stderr, "No such file");
}
