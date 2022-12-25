#include "sorts.h"
#include "main.h"

// Comparators
int name_compare_direct(const void *v1, const void *v2) {
    voter *voter1 = (voter*)v1;
    voter *voter2 = (voter*)v2;
    return strcmp(voter1->name, voter2->name);
}

int polling_n_compare_direct(const void *v1, const void *v2) {
    voter *voter1 = (voter*)v1;
    voter *voter2 = (voter*)v2;
    return strcmp(voter1->polling_n, voter2->polling_n);
}

int age_compare_direct(const void *v1, const void *v2) {
    voter voter1 = *(voter*)v1;
    voter voter2 = *(voter*)v2;

    int compare = 0;
    if (voter1.age > voter2.age) compare = 1;
    if (voter1.age < voter2.age) compare = -1;

    return compare;
}

int name_compare_reverse(const void *v1, const void *v2) {
    voter *voter1 = (voter*)v1;
    voter *voter2 = (voter*)v2;
    return -1 * strcmp(voter1->name, voter2->name);
}

int polling_n_compare_reverse(const void *v1, const void *v2) {
    voter *voter1 = (voter*)v1;
    voter *voter2 = (voter*)v2;
    return -1 * strcmp(voter1->polling_n, voter2->polling_n);
}

int age_compare_reverse(const void *v1, const void *v2) {
    voter voter1 = *(voter*)v1;
    voter voter2 = *(voter*)v2;

    int compare = 0;
    if (voter1.age > voter2.age) compare = 1;
    if (voter1.age < voter2.age) compare = -1;

    return -1 * compare;
}

// Sorts
void shell_sort(void *voters, int num, int comparator(const void *, const void *)) {
    for (int step = num / 2; step > 0; step /= 2) {
        for (int i = step; i < num; i += 1) {
            voter temp = ((voter*)voters)[i];
            int j = 0;
            for (j = i; j >= step; j -= step) {                
                if (comparator(&((voter*)voters)[j - step], &temp) == 1)
                ((voter*)voters)[j] = ((voter*)voters)[j - step];
            }
            ((voter*)voters)[j] = temp;
        }
    }
}

void comb_sort(void *voters, int num, int comparator(const void *, const void *)) {
    int step = num;
    int flag = 1;

    while (flag && step >= 1) {
        flag = 0;

        for (int i = 0; i + step < num; i++) {
            if (comparator(&((voter*)voters)[i], &((voter*)voters)[i + step]) == 1) {
                swap_voters(&((voter*)voters)[i], &((voter*)voters)[i + step]);
                flag = 1;
            }    
        }

        step /= REDUCTION_FACTOR;
    }
}

void sortq(void *voters, int num, int comparator(const void *, const void *)) {
    qsort(voters, num, sizeof(voter), comparator);
}
