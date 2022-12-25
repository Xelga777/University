#include "main.h"

int main(int argc, char **argv) {
    int err_code = 0;
    int voters_count = 0;
    Options options = {0, 0, 0, NULL, NULL};
    voter *voters = {NULL};

    err_code = parse_str(argc, argv, &options);
    if (!err_code) get_structs(options.filename_in, &voters, &voters_count);
    if (!err_code) call_sort(options, voters, voters_count);
    if (!err_code) output(options.filename_out, voters, voters_count);

    if (err_code) err_handler(err_code);
    if (voters) free_structs(voters, voters_count);
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


void get_structs(const char *filename, voter **voters, int* voters_count) {
    FILE *fp = fopen(filename, "r");
    FILE *fp_cpy = fopen(filename, "r");

    char *line = NULL, *ptr = NULL;
    char age_str[MAX_INT] = {0};
    char ch = 0;
    int str_len = 0, len_name = 0;

    *voters_count = get_structs_num(fp);
    printf("COUNT: %d\n", *voters_count);
    *voters = malloc(*voters_count * sizeof(voter));
    voter *voter_ptr = *voters;

    fp = fopen(filename, "r");

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

        len_name = get_name(line, &(voter_ptr->name));
        ptr = line + len_name;
        sscanf(ptr, "%s%s",voter_ptr->polling_n, age_str);
        voter_ptr->age = atoi(age_str);

        // TEST OUT:
        // printf("NAME: %s\nPOLLING_N: %s\nAGE: %d\n\n", voter_ptr->name, voter_ptr->polling_n, voter_ptr->age);

        voter_ptr++;
        free(line);
    }

    fclose(fp);
    fclose(fp_cpy);
}

int get_structs_num(FILE *fp) {
    char ch = 0;
    int lines_num = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%c", &ch);
        if (ch == '\n') lines_num += 1;
    }
    fclose(fp);
    return lines_num + 1;
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

int get_name(char *str, char **name) {
    int len = 0, count_sp = 0;
    char ch = 1;

    while (ch && ch != '\n' && count_sp < 3) {
        sscanf(str, "%c", &ch);
        str++;
        len += 1;
        if (ch == ' ') count_sp += 1;
    }

    str -= len;
    *name = (char*)calloc(len, sizeof(char));
    memcpy(*name, str, len * sizeof(char));
    (*name)[len - 1] = '\0';

    if (ch == -1) {
        return 0;
    } else {
        return len - 1;
    }
}

void call_sort(Options options, voter *voters, int voters_count) {
    if (options.sort == 'q' || options.sort == 0) {
        if (options.field == 'n' || options.field == 0) {
            if (options.direction == 'd' || options.direction == 0) {
                sortq(voters, voters_count, name_compare_direct);
            } else {
                sortq(voters, voters_count, name_compare_reverse);
            }
        } else if (options.field == 'p') {
            if (options.direction == 'd' || options.direction == 0) {
                sortq(voters, voters_count, polling_n_compare_direct);
            } else {
                sortq(voters, voters_count, polling_n_compare_reverse);
            }
        } else if (options.field == 'a') {
            if (options.direction == 'd' || options.direction == 0) {
                sortq(voters, voters_count, age_compare_direct);
            } else {
                sortq(voters, voters_count, age_compare_reverse);
            }
        }
    } else if (options.sort == 'c') {
        if (options.field == 'n' || options.field == 0) {
            if (options.direction == 'd' || options.direction == 0) {
                comb_sort(voters, voters_count, name_compare_direct);
            } else {
                comb_sort(voters, voters_count, name_compare_reverse);
            }
        } else if (options.field == 'p') {
            if (options.direction == 'd' || options.direction == 0) {
                comb_sort(voters, voters_count, polling_n_compare_direct);
            } else {
                comb_sort(voters, voters_count, polling_n_compare_reverse);
            }
        } else if (options.field == 'a') {
            if (options.direction == 'd' || options.direction == 0) {
                comb_sort(voters, voters_count, age_compare_direct);
            } else {
                comb_sort(voters, voters_count, age_compare_reverse);
            }            
        }
    } else if (options.sort == 's') {
        if (options.field == 'n' || options.field == 0) {
            if (options.direction == 'd' || options.direction == 0) {
                shell_sort(voters, voters_count, name_compare_direct);
            } else {
                shell_sort(voters, voters_count, name_compare_reverse);
            }
        } else if (options.field == 'p') {
            if (options.direction == 'd' || options.direction == 0) {
                shell_sort(voters, voters_count, polling_n_compare_direct);
            } else {
                shell_sort(voters, voters_count, polling_n_compare_reverse);
            }
        } else if (options.field == 'a') {
            if (options.direction == 'd' || options.direction == 0) {
                shell_sort(voters, voters_count, age_compare_direct);
            } else {
                shell_sort(voters, voters_count, age_compare_reverse);
            }    
        }
    }
}

void output(char *filename, voter *voters, int voters_count) {
    FILE *fp = fopen(filename, "a");

    for (int i = 0; i < voters_count; i++) {
        fprintf(fp, "%s %s %d\n", (voters[i]).name, (voters[i]).polling_n, (voters[i]).age);
    }

    fclose(fp);
}
