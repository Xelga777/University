#include "token.h"

double my_pow(int num);

struct token *tokens_gen(const char *string, int str_length, int *length) {
    struct token *array = malloc(++(*length) * sizeof(struct token));
    for (int i = 0, ind = 0; i < str_length; ind++) {
        char current_el = *(string + i++);
        if (current_el == 'x') {
            array[ind].type = VAR;
        } else if (current_el == '+') {
            array[ind].type = SUM;
            array[ind].priority = 0;
        } else if (current_el == '-') {
            array[ind].type = SUB;
            array[ind].priority = 0;
        } else if (current_el == '*') {
            array[ind].type = MUL;
            array[ind].priority = 1;
        } else if (current_el == '/') {
            array[ind].type = DIV;
            array[ind].priority = 1;
        } else if (current_el == '(') {
            array[ind].type = BRo;
        } else if (current_el == ')') {
            array[ind].type = BRc;
        } else if ('a' <= current_el && current_el <= 'z') {
            char str[5];
            int len = 1;
            while (i < str_length && len < 5 && 'a' <= current_el && current_el <= 'z') {
                str[len++ - 1] = current_el;
                current_el = *(string + i++);
            }
            if (i == str_length) {free(array);
                array = NULL;
                break;
            }
            str[--len] = '\0';
            i--;
            if (!strcmp(str, "sin")) {
                array[ind].type = SIN;
            } else if (!strcmp(str, "cos")) {
                array[ind].type = COS;
            } else if (!strcmp(str, "tan")) {
                array[ind].type = TAN;
            } else if (!strcmp(str, "ctg")) {
                array[ind].type = CTG;
            } else if (!strcmp(str, "sqrt")) {
                array[ind].type = SQRT;
            } else if (!strcmp(str, "ln")) {
                array[ind].type = LN;
            } else {
                free(array);
                array = NULL;
                break;
            }
        } else if ('0' <= current_el && current_el <= '9') {
            int dots = 0, len = 1, dot_i = 0;
            double result = 0;
            char *nums = malloc(len * sizeof(char));
            while ((dots == 0 && current_el == '.') || ('0' <= current_el && current_el <= '9')) {
                if (current_el == '.') {
                    dots++;
                    dot_i = len - 1;
                }
                nums[len++ - 1] = current_el;
                current_el = *(string + i++);
                void *tmp = realloc(nums, len * sizeof(char));

                if (NULL != tmp) {
                    nums = tmp;
                }
            }
            nums[--len] = '\0';
            i--;
            if (dot_i) {
                for (int j = 0; j < dot_i; j++) { result += (nums[j] - '0') * my_pow(dot_i - j - 1); }
                for (int j = dot_i + 1; j < len; j++) { result += (nums[j] - '0') * my_pow(dot_i - j); }
            } else {
                for (int j = 0; j < len; j++) {result += (nums[j] - '0') * my_pow(len - j - 1);}
            }
            array[ind].type = NUM;
            array[ind].value = result;
            free(nums);

        } else {free(array); array = NULL; break;}
        void *tmp = realloc(array, ++(*length) * sizeof(struct token));

        if (NULL != tmp) {
            array = tmp;
        }
    }
    return array;
}

struct token *tokens_control(struct token *array, int length) {
    for (int i = 0; i < length; i++) {
        if (array[i].type == SUB && (i == 0 || array[i - 1].type == SUM || array[i - 1].type == SUB
        || array[i - 1].type == MUL || array[i - 1].type == DIV || array[i - 1].type == BRo)) {
            array[i].type = USUB;
            array[i].priority = 2;
        }
    }

    for (int i = 1; i < length; i++) {
        if (((SUM <= array[i - 1].type && array[i - 1].type <= DIV) &&
            (SUM <= array[i].type && array[i].type <= DIV) && array[i].type != USUB)
            || (array[i - 1].type == BRo && SUM <= array[i].type && array[i].type <= DIV &&
            array[i].type != USUB) || (SUM <= array[i - 1].type &&
            array[i - 1].type <= DIV && array[i].type == BRc) || (array[i - 1].type == BRo &&
            array[i].type == BRc)) {
            free(array);
            array = NULL;
            break;
        }
    }

    if (array && (!(array[0].type == USUB || array[0].type == NUM || array[0].type == VAR ||
        array[0].type == BRo || (9 <= array[0].type && array[0].type <= 14)) ||
        !(array[length - 1].type == VAR || array[length - 1].type == NUM || array[length - 1].type == BRc))) {
        free(array);
        array = NULL;
    }

    return array;
}

double my_pow(int num) {
    double result = 1;
    if (num == 0) {
        result = 1;
    } else if (num > 0) {
        for (int i = 1; i <= num; i++) {result *= 10;}
    } else {
        for (int i = num; i < 0; i++) {result /= 10;}
    }
    return result;
}
