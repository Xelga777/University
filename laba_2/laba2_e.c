#include <stdio.h>

void input(float* e, float* x);
float computation(float e, int* n, float x);

int main() {
    float x = 0, e = 0;
    int n = 1;
    input(&e, &x);
    printf("Значение функции в заданной точке: %f\n", computation(e, &n, x));
    printf("Количество просуммированных членов ряда: %d", n);
    return 0;
}

void input(float* e, float* x) {
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

    printf("Введите точность вычисления\n");
    while (flag) {
        if ((scanf("%f", e)) && (*e > 0) && (*e < 1)) {
            flag = 0;
        } else if ((*e <= 0) || (*e >= 1)) {
            printf("Точность вычисления функции должна быть больше 0 и меньше 1\n");
            *e = 0.5;
            scanf("%*[^\n]");
        } else {
            printf("Некорректное значение, повторите ввод\n");
            scanf("%*[^\n]");
        }
    }
}

float computation(float e, int* n, float x) {
    float result = 1, x_i = 1;
    while (x_i > e) {
        x_i *= x * (3 - 2 * (*n)) / (2 * (*n));
        result += x_i;
        *n += 1;
    }
    return result;
}
