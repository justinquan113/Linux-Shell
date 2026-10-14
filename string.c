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