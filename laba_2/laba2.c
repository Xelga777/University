#include <stdio.h>

void input(int* n, float* x);
float computation(int n, float x);

int main() {
    float x = 0;
    int n = 1;
    input(&n, &x);
    printf("Значение функции в заданной точке: %f", computation(n, x));
    return 0;
}

void input(int* n, float* x) {
    int flag = 0;
    printf("Введите значение аргумента\n");
    while (!flag) {
        if ((scanf("%f", x)) && (*x >= -1) && (*x <= 1)) {
            flag = 1;
        } else if ((*x < -1) || (*x > 1)) {
            printf("Значение аргумента не входит в область определения функции, модуль x обязан быть не больше 1\n");
            scanf("%*[^\n]");
            *x = 0;
        } else {
            printf("Некорректное значение аргумента, повторите ввод\n");
            scanf("%*[^\n]");
        }
    }

    printf("Введите количество членов ряда\n");
    while (flag) {
        scanf("%*[^\n]");
        if ((scanf("%d", n)) && (*n > 0)) {
            flag = 0;
        } else if (*n <= 0) {
            printf("Количество суммируемых членов должно быть больше 0\n");
            *n = 1;
        } else {
            printf("Некорректное значение, повторите ввод\n");
        }
    }
}

float computation(int n, float x) {
    float result = 1;
    float x_i = 1;
    for (int i = 1; i < n; i++) {
        x_i *= x * (3 - 2 * i) / (2 * i);
        result += x_i;
    }
    return result;
}
