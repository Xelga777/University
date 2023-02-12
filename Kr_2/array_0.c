#include <stdio.h>
#include <stdlib.h>

void input(int *n, int **array);
void func(int *n, int **array);
void step(int n, int *array, int index);
void output(int n, int *array);

int main() {
    int n = 0;
    int *arr = NULL;
    input(&n, &arr);
    // output(n, arr);
    func(&n, &arr);
    output(n, arr);

    if (arr) free(arr);
}

void input(int *n, int **array) {
    scanf("%d", n);
    // printf("NUM: %d", *n);
    *array = calloc(*n, sizeof(int));

    for (int i = 0; i < *n; i++) {
        scanf("%d", &((*array)[i]));
    }
}

void func(int *n, int **array) {
    int *ptr = *array;

    for (int i = 0; i < *n; i++) {
        if (!(ptr[i] % 2)) {
            ptr[i] = ptr[i] / 2;
            *n += 1;
            ptr = realloc(ptr, *n * sizeof(int));
            step(*n, ptr, i);
            ptr[i + 1] = ptr[i];
            i += 1;
        }    
    }
    
    *array = ptr;
}

void step(int n, int *array, int index) {
    int cur = 0, prev = array[index];
    for (int i = index; i < n; i++) {
        cur = array[i];
        array[i] = prev;
        prev = cur;
    }
}

void output(int n, int *array) {
    for (int *p = array; p - array < n; p++) printf("%d ", *p);
}
