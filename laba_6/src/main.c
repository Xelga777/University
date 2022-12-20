#include "main.h"

int main() {
    node *string = NULL;
    char ch = 0;
    int final = 0;

    while (final == 0) {
        string = getstr(&final, ch);

        printf("BEFORE: ");
        output(string);

        delete_consonants(string);

        printf("AFTER:  ");
        output(string);

        destroy(string);
    }
    return 0;
}

node *getstr(int *final, char c) {
    c = getchar();
    node *string = init(c);
    node *ptr = string;
    while (1) {
        c = getchar();
        if (c == -1) {
            *final = 1;
            break;
        }
        ptr = add_ch(ptr, c);

        if (c == 10) { 
            break;
        }
    }
    return string;
}

void delete_consonants(node *string) {
    node *ptr = string;
    char c = 0;
    int counter_sp = 0;
    const char consonants[21] = "BCDFGHJKLMNPQRSTVWXZ";
    while (ptr -> next) {
        c = ptr -> ch;
        for (int i = 0; i < CONSONANTS_NUM; i++) {
            if (c == consonants[i] || c == consonants[i] + UPPER_TO_LOW) {
                ptr = remove_ch(ptr, string);
            }
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
        if (counter_sp > 1) ptr = remove_ch(ptr, string);
        ptr = ptr -> next;
    }
}

void output(node *string) {
    printf("\"");
    while (string -> next) {
        printf("%c", string->ch);
        string = string -> next;
    }
    printf("\"\n");
}
