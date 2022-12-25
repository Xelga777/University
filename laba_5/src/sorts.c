#include "sorts.h"
#include "main.h"

// Comparators
int name_compare_direct(const void *v1, const void *v2) {
    return strcmp(((voter*)v1)->name, ((voter*)v2)->name);
}

int polling_n_compare_direct(const void *v1, const void *v2) {
    return strcmp(((voter*)v1)->polling_n, ((voter*)v2)->polling_n);
}

int age_compare_direct(const void *v1, const void *v2) {
    int compare = 0;
    if (((voter*)v1)->age > ((voter*)v2)->age) compare = 1;
    if (((voter*)v1)->age < ((voter*)v2)->age) compare = -1;

    return compare;
}

int name_compare_reverse(const void *v1, const void *v2) {
    return -1 * strcmp(((voter*)v1)->name, ((voter*)v2)->name);
}

int polling_n_compare_reverse(const void *v1, const void *v2) {
    return -1 * strcmp(((voter*)v1)->polling_n, ((voter*)v2)->polling_n);
}

int age_compare_reverse(const void *v1, const void *v2) {
    int compare = 0;
    if (((voter*)v1)->age > ((voter*)v2)->age) compare = 1;
    if (((voter*)v1)->age < ((voter*)v2)->age) compare = -1;

    return -1 * compare;
}

// Sorts
void shell_sort(void *voters, int num, int comparator(const void *, const void *)) {
    for (int step = num / 2; step > 0; step /= 2) {
        for (int i = step; i < num; ++i) {
            for (int j = i - step; j >= 0; j -= step) {                
                if (comparator(&((voter*)voters)[j], &((voter*)voters)[j + step]) == 1)
                swap_voters(&((voter*)voters)[j], &((voter*)voters)[j + step]);
            }
        }
    }
}

void comb_sort(void *voters, int num, int comparator(const void *, const void *)) {
    int step = num - 1;

    while (step >= 1) {

        for (int i = 0; i + step < num; i++) {
            if (comparator(&((voter*)voters)[i], &((voter*)voters)[i + step]) == 1) {
                swap_voters(&((voter*)voters)[i], &((voter*)voters)[i + step]);
            }    
        }

        step /= REDUCTION_FACTOR;
    }
}

void sortq(void *voters, int num, int comparator(const void *, const void *)) {
    qsort(voters, num, sizeof(voter), comparator);
}
