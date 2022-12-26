#include "statistics.h"

int main(int argc, char** argv) {
    int err_code = 0;
    Options options = {0};
    err_code = parse_str(argc, argv, &options);
    if (!err_code) make_test(options);

    if (err_code) err_handler(err_code);
    return 0;
}

int parse_str(int argc, char **argv, Options *options) {
    int err_code = 0;
    int opt = 0;

    Options check_duplicates = {0};

    if (argc < 5) err_code = -1;

    while (opt != -1) {
        if (err_code) break;

        opt = getopt(argc, argv, "e:v:rdnpacsq");

        if ((opt == 'c' || opt == 's' || opt == 'q') && !check_duplicates.sort) {
            (*options).sort = opt;
            check_duplicates.sort = 1;
        } else if ((opt == 'n' || opt == 'p' || opt == 'a') && !check_duplicates.field) {
            (*options).field = opt;
            check_duplicates.field = 1;
        } else if ((opt == 'r' || opt == 'd') && !check_duplicates.direction) {
            (*options).direction = opt;
            check_duplicates.direction = 1;
        } else if (opt == 'e' && !check_duplicates.elements_num) {
            (*options).elements_num = atoi(optarg);
            check_duplicates.elements_num = 1;
        } else if (opt == 'v' && !check_duplicates.arrays_num) {
            (*options).arrays_num = atoi(optarg);
            check_duplicates.arrays_num = 1;
        } else if (opt == '?') {
            err_code = -2;
        }
    }

    return err_code;
}

void make_test(Options options) {
    // Creating data:
    voter **voters = calloc(options.arrays_num, sizeof(voter*));

    for (int i = 0; i < options.arrays_num; i++) {
        voters[i] = calloc(options.elements_num, sizeof(voter));

        for (int j = 0; j < options.elements_num; j++) {
            (voters[i][j]).name = create_name();
            create_polling_n((voters[i][j]).polling_n);
            (voters[i][j]).age = create_age();           
        }
    }


    // Making test:
    double time_spent = 0.0;
    clock_t begin = clock();

    for (int i = 0; i < options.arrays_num; i++) {
        call_sort(options, voters[i], options.elements_num);
    }

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds", time_spent);


    // Clearing data:
    for (int i = 0; i < options.arrays_num; i++) {
        free_structs(voters[i], options.elements_num);
    }
    free(voters);

    // TEST OUT:
    // for (int i = 0; i < options.arrays_num; i++) {
    //     for (int j = 0; j < options.elements_num; j++) {
    //         printf("NAME: %s\n", (voters[i][j]).name);
    //     }
    //     printf("\n\n\n");
    // }
}

char *create_name() {
    char *name = (char*)calloc(NAME_LEN + 1, sizeof(char));
    for (int i = 0; i < NAME_LEN; i++) {
        srand((int)clock());
        name[i] = (char)(rand() % 26 + 97);
    }
    
    return name;
}

void create_polling_n(char polling_n[7]) {
    for (int i = 0; i < 3; i++) {
        srand((int)clock());
        polling_n[i] = (char)(rand() % 26 + 97);
    }
    polling_n[3] = '-';
    for (int i = 4; i < 7; i++) {
        srand((int)clock());
        polling_n[i] = rand() % 10 + 48;
    }
}

int create_age() {
    int age = 0;

    srand((int)clock());
    age += (rand() % 10 + 48) * 10;
    srand((int)clock());
    age += rand() % 10 + 48;

    return age;
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
