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
    node *root = *string;
    char c = 0;
    int counter_sp = 0;
    int whereAmI = 0;
    const char consonants[21] = "BCDFGHJKLMNPQRSTVWXZ";
    while (*string) {
        whereAmI += 1;
        c = (*string) -> ch;
        for (int i = 0; i < CONSONANTS_NUM; i++) {
            if (c == consonants[i] || c == consonants[i] + UPPER_TO_LOW) {
                *string = remove_ch(*string, root);
                whereAmI -= 1;
                break;
            }
        }

        if (!*string) {
            break;
        }

        if (c == '\t') {
            (*string) -> ch = ' ';
            c = ' ';
        }
        if (c == ' ') {
            counter_sp += 1;
        } else {
            counter_sp = 0;
        }
        if (counter_sp > 1) {
            *string = remove_ch(*string, root);
            whereAmI -= 1;
        }

        if (!whereAmI) {
            root = *string;
        } else {
            *string = (*string) -> next;
        }
    }

    if (whereAmI) *string = root;
}

void output(node *string) {
    printf("\"");
    while (string != NULL) {
        printf("%c", string -> ch);
        string = string -> next;
    }
    printf("\"\n");
}
