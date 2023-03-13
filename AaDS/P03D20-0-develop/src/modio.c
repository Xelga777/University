#include "modio.h"

char *input(int *length) {
    *length = 1;
    char *string = malloc(*length * sizeof(char)), element;

    scanf("%c", &element);

    while (element != '\n') {
        if (element != ' ') {
            string[(*length)++ - 1] = element;
            void *tmp = realloc(string, (*length) * sizeof(char));
            if (NULL != tmp) {
                string = tmp;
            }
        }
        scanf("%c", &element);
    }
    --(*length);
    return string;
}


void output(struct token *root) {
    int flag = ERR_OK;
    double height_step = ((double)2 / HEIGHT);
    double width_step = ((double)W_AMP / WIDTH);
    double x_step = (W_AMP / WIDTH);


    for (double i = -1; i < 1; i += height_step) {
        double x = 0;
        for (double j = 0; j < W_AMP; j += width_step) {
            x += x_step;
            double y = (*root->eval) (root, x, &flag);
            if ((y <= (i + ACCURANCY)) && (y >= (i - ACCURANCY))) {
                printf("%c", NON_EMPTY_C);
            } else {
                printf("%c", EMPTY_C);
            }
        }
        if (i != (1 - height_step)) {
            printf("\n");
        }
    }
}

