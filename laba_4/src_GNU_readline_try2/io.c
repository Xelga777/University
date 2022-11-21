#include "io.h"

void output(char *src, char *dst) {
    printf("\n###RESULT###\n");
    if (src && *src != EOF) {
        printf("ORIGINAL: \"%s\"\n", src);
    }
    if (dst && *dst != EOF) {
        printf("COMPUTED: \"%s\"\n\n", dst);
    }
}
