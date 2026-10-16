#include <stdio.h>
#include "string.h"

int main(void)
{
    int passed = 0;
    int total = 0;

    /* Test mystrlen */
    total++;
    if (mystrlen("hello") == 5) {
        printf("PASS: mystrlen normal string\n");
        passed++;
    } else {
        printf("FAIL: mystrlen normal string\n");
    }

    total++;
    if (mystrlen("") == 0) {
        printf("PASS: mystrlen empty string\n");
        passed++;
    } else {
        printf("FAIL: mystrlen empty string\n");
    }

    /* Test mystrcmp */
    total++;
    if (mystrcmp("exit", "exit") == 0) {
        printf("PASS: mystrcmp equal strings\n");
        passed++;
    } else {
        printf("FAIL: mystrcmp equal strings\n");
    }

    total++;
    if (mystrcmp("hello", "world") != 0) {
        printf("PASS: mystrcmp different strings\n");
        passed++;
    } else {
        printf("FAIL: mystrcmp different strings\n");
    }

    total++;
    if (mystrcmp("abc", "ab") != 0) {
        printf("PASS: mystrcmp different lengths\n");
        passed++;
    } else {
        printf("FAIL: mystrcmp different lengths\n");
    }

    /* Test mystrcpy */
    char destination[20];

    total++;
    mystrcpy(destination, "hello");

    if (mystrcmp(destination, "hello") == 0) {
        printf("PASS: mystrcpy copies string\n");
        passed++;
    } else {
        printf("FAIL: mystrcpy copies string\n");
    }

    total++;
    mystrcpy(destination, "");

    if (destination[0] == '\0') {
        printf("PASS: mystrcpy empty string\n");
        passed++;
    } else {
        printf("FAIL: mystrcpy empty string\n");
    }

    printf("\nString tests: %d/%d passed\n", passed, total);

    return passed == total ? 0 : 1;
}