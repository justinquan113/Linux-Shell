#include "string.h"

unsigned int mystrlen(const char *s){
    int count = 0;
    while(*s != '\0'){
        count++;
        s++;
    }

    return count;
}

int mystrcmp(const char *s1, const char *s2){
    while (*s1 != '\0' && *s2 != '\0'){
        if (*s1 != *s2){
            return 1;
        }
        s1++;
        s2++;
    }
    
    return *s1 != *s2;
}

/*Reference: https://www.geeksforgeeks.org/c/implement-itoa/ */
/*Changes an int to char*/
char *myitoa(int n, char *buf, unsigned int size){
    unsigned int i = size - 1;
    int negative = 0;

    buf[i] = '\0';

    /* the digit loop never runs for 0, so it needs its own case */
    if (n == 0){
        i--;
        buf[i] = '0';
        return &buf[i];
    }

    if (n < 0){
        negative = 1;
    }

    while (n != 0){
        /* work on the remainder without flipping the sign, so the most
           negative int does not overflow */
        int digit = n % 10;

        if (digit < 0){
            digit = -digit;
        }

        i--;
        buf[i] = '0' + digit;
        n = n / 10;
    }

    if (negative){
        i--;
        buf[i] = '-';
    }

    return &buf[i];
}

char *mystrcpy(char *dest, const char *src){
    int i = 0;
    while(*src != '\0'){
        dest[i] = *src;
        src++;
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *mystrcat(char *dest, const char*src) {
    int i = 0;
    int j = 0;

    // go to end of the destination string
    while (dest[i] != '\0') {
        i++;
    }

    while (src[j] != '\0') {
        dest[i] = src[j];
        i++;
        j++;
    }

    dest[i] = '\0';
    return dest;
}