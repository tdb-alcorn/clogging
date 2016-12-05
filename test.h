#include <stdio.h>

void test(char* name, int prop) {
    if (prop) {
        printf(".");
        return;
    }
    printf("X\nTest failed: %s\n", name);
}

