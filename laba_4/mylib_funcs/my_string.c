#include "my_string.h"

int my_readline(char **line) {
    char *buffer = (char*)calloc(1024, sizeof(char));
    int err_code = scanf("%1024[^\n]", buffer);
    scanf("%*c");
    int len_str = 0;
    char* ptr = NULL;

    len_str = my_strlen(buffer);
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

int my_strlen(char *str) {
    int length = 0;
    while (*str) {
        length += 1;
        str += 1;
    }
    return length;
}

int my_atoi(char *str) {
    int number = 0;
    char *ptr = str;


    while (ptr && ((*ptr >= '0' && *ptr <= '9') || (*ptr == '-' && *(ptr + 1) >= '0' && *(ptr + 1) <= '9'))) {
        number *= 10;
        number += get_digit(ptr);
        ptr++;
    }

    return number;
}

int get_digit(char *ptr) {
    int digit;
    if (*ptr == '0') digit = 0;
    else if (*ptr == '1') digit = 1;
    else if (*ptr == '2') digit = 2;
    else if (*ptr == '3') digit = 3;
    else if (*ptr == '4') digit = 4;
    else if (*ptr == '5') digit = 5;
    else if (*ptr == '6') digit = 6;
    else if (*ptr == '7') digit = 7;
    else if (*ptr == '8') digit = 8;
    else if (*ptr == '9') digit = 9;
    else {
        digit = -1;
    }
    return digit;
}