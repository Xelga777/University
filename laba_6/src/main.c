#include "main.h"

int main() {
    node *string = NULL;
    char ch = 0;
    int final = 0;

    while (final == 0) {
        string = getstr(&final, ch);

        if (!string) break;

        printf("BEFORE: ");
        output(string);

        delete_consonants(&string);

        printf("AFTER:  ");
        output(string);

        if (string != NULL) destroy(string);
    }
    return 0;
}

node *getstr(int *final, char c) {
    c = getchar();

    if (c == -1) {
        *final = 1;
        return NULL;
    }

    node *string = init(c);
    node *ptr = string;
    while (1) {
        c = getchar();
        if (c == -1) {
            *final = 1;
            break;
        } else if (c == 10) break;
        ptr = add_ch(ptr, c);
    }
    return string;
}

void delete_consonants(node **string) {
    node *ptr = *string;
    char c = 0;
    int counter_sp = 0;
    int is_root = 1;
    const char consonants[21] = "BCDFGHJKLMNPQRSTVWXZ";
    while (ptr) {
        c = ptr -> ch;
        for (int i = 0; i < CONSONANTS_NUM; i++) {
            if (c == consonants[i] || c == consonants[i] + UPPER_TO_LOW) {
                ptr = remove_ch(ptr, *string);
                break;
            }
        }

        if (!ptr) {
            *string = NULL;
            break;
        } else if (is_root) {
            *string = ptr;
        }
        if (c == '\t') {
            ptr -> ch = ' ';
            c = ' ';
        }
        if (c == ' ') {
            counter_sp += 1;
        } else {
            counter_sp = 0;
        }
        if (counter_sp > 1) ptr = remove_ch(ptr, *string);
        ptr = ptr -> next;
        is_root = 0;
    }
}

void output(node *string) {
    printf("\"");
    while (string != NULL) {
        printf("%c", string -> ch);
        string = string -> next;
    }
    printf("\"\n");
}
