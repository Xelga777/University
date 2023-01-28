#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_delims(char *str, int len);
int my_readline(char **line);
void step(int n, char *array, int index);
void func(char **str, int *len);
void output(char *str, int len);

int main() {
    char *str = NULL;
    int len = my_readline(&str);

    str = remove_delims(str, len);
    func(&str, &len);
    output(str, len);

    free(str);
    return 0;
}

char *remove_delims(char *str, int len) {
    char *cpy = calloc(len, sizeof(char));
    int count = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == '\t') str[i] = ' ';
        cpy[i] = str[i];

        while (str[i] == ' ' && str[i + 1] == ' ') {    
            i += 1;
            count += 1;
        }
    }

    free(str);
    return cpy;
}

void func(char **str, int *len) {
    char *ptr = *str;

    for (int i = 0; i < *len; i++) {
        if (ptr[i] >= 'A' && ptr[i] <= 'Z') {
            *len += 1;
            ptr = realloc(ptr, *len * sizeof(char));
            step(*len, ptr, ++i);
            ptr[i] = ptr[i - 1];
        }
    }
    *str = ptr;
}

void step(int n, char *array, int index) {
    char cur = 0, prev = array[index];
    for (int i = index; i < n; i++) {
        cur = array[i];
        array[i] = prev;
        prev = cur;
    }
}

void output(char *str, int len) {
    for (char *p = str; p - str < len; p++) printf("%c", *p);
}

int my_readline(char **line) {
    char *buffer = (char*)calloc(1024, sizeof(char));
    int err_code = scanf("%1024[^\n]", buffer);
    scanf("%*c");
    int len_str = 0;
    char* ptr = NULL;

    len_str = strlen(buffer);
    if (err_code != -1) {
        if (!*line) free(*line);
        *line = (char*)calloc(len_str + 2, sizeof(char));
        ptr = *line;
        for (int i = 0; i < len_str; i++) ptr[i] = buffer[i];
        (*line)[len_str] = '\0';
    } else {
        *line = 0;
    }
    free(buffer);
    return len_str;
}
