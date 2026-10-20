#include <stdio.h>
#include "mystring.h"

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

    
    /* Test myitoa */
    char buffer[20];
    char *result;

    total++;
    result = myitoa(12345, buffer, sizeof(buffer));
    if (mystrcmp(result, "12345") == 0) {
        printf("PASS: myitoa positive number\n");
        passed++;
    } else {
        printf("FAIL: myitoa positive number\n");
    }

    total++;
    result = myitoa(-123, buffer, sizeof(buffer));
    if (mystrcmp(result, "-123") == 0) {
        printf("PASS: myitoa negative number\n");
        passed++;
    } else {
        printf("FAIL: myitoa negative number\n");
    }

    total++;
    result = myitoa(0, buffer, sizeof(buffer));
    if (mystrcmp(result, "0") == 0) {
        printf("PASS: myitoa zero\n");
        passed++;
    } else {
        printf("FAIL: myitoa zero\n");
    }

    /* Test mystrcat */
    char concat_destination[30];

    total++;
    mystrcpy(concat_destination, "Hello");
    mystrcat(concat_destination, " World");

    if (mystrcmp(concat_destination, "Hello World") == 0) {
        printf("PASS: mystrcat joins two strings\n");
        passed++;
    } else {
        printf("FAIL: mystrcat joins two strings\n");
    }

    total++;
    mystrcpy(concat_destination, "Hello");
    mystrcat(concat_destination, "");

    if (mystrcmp(concat_destination, "Hello") == 0) {
        printf("PASS: mystrcat with empty source\n");
        passed++;
    } else {
        printf("FAIL: mystrcat with empty source\n");
    }

    total++;
    mystrcpy(concat_destination, "");
    mystrcat(concat_destination, "World");

    if (mystrcmp(concat_destination, "World") == 0) {
        printf("PASS: mystrcat with empty destination\n");
        passed++;
    } else {
        printf("FAIL: mystrcat with empty destination\n");
    }
    
    printf("\nString tests: %d/%d passed\n", passed, total);

    return passed == total ? 0 : 1;
}
