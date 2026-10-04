#include "string.h"
#include <string.h>
#include <stdio.h>


void mystrlen_test(int expected, const char *test_input){
    int length = mystrlen(test_input);
    printf("String Length Test\n");
    printf("Test Case: %s\n", test_input);
    printf("Expected Output: %d\n", expected);
    printf("Actual Output: %d\n", length);

    if(length == expected){
        printf("TEST PASSED\n\n");
    }
    else{
        printf("TEST FAILED\n\n");
    }
}

void mystrcmp_test(const char* test_input, int expected){
    char *input = "abc";
    int result = mystrcmp(test_input, input);
    printf("String Compare Test\n");
    printf("Test Case: %s %s\n", test_input, input);
    printf("Expected Output %d\n", expected);
    printf("Actual Output %d\n", result);
    
    if(result == 0){
        printf("TEST PASSED\n\n");
    }

    else if(result == 1){
        printf("TEST PASSED\n\n");
    }

    else{
        printf("TEST FAILED\n\n");
    }
}

void mystrcpy_test(const char *test_input){
    char s[50];
    mystrcpy(s, test_input); 
    printf("String Copy Test\n");
    printf("Test Case: %s\n", test_input);
    printf("Expected Output: %s\n", test_input);
    printf("Actual Output: %s\n", s);

    if(mystrcmp(s, test_input) == 0){
        printf("TEST PASSED\n\n");
    }

    else{
        printf("TEST FAILED\n\n");
    }
}


int main(){
    const char *test_input = "hello world";
    const char *test_input1 = "";
    const char *test_input2 = "abc";
    const char *test_input3 = "abd";
    mystrlen_test(strlen(test_input) , test_input);
    mystrlen_test(strlen(test_input1), test_input1);
    mystrcmp_test(test_input2, 0);
    mystrcmp_test(test_input3, 1);
    mystrcpy_test(test_input);
    
    return 0;
}
