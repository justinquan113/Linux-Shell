#ifndef MYSTRING_H
#define MYSTRING_H
unsigned int mystrlen(const char *s);

int mystrcmp(const char *s1, const char *s2);

char *mystrcpy(char *dest, const char *src);

/* enough for the sign, 10 digits of a 32 bit int, and the terminator */
#define MYITOA_BUF 12

/* converts n to digits inside buf and returns a pointer to the first one */
char *myitoa(int n, char *buf, unsigned int size);
char *mystrcat(char *dest, const char*src);

#endif
