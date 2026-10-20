#include <stdio.h> 
#include "execute.h" 
#include "mystring.h" 
#include "myheap.h"

void run_test( const char *test_name, char *command, char *envp[], const char *expected_path ) { 
    /* Reset memory before each test */ 
    free_all();

    printf("Test case: %s\n", test_name);
    printf("Command: \"%s\"\n", command);

    char *result = resolve_path(command, envp);

    /* Check whether the resolved path matches the expected path */
    if (expected_path == NULL) {
        if (result == NULL) {
            printf("PASS: command not found\n");
        } else {
            printf("FAIL: expected command not to be found, got \"%s\"\n",
                result);
        }
    } else if (result != NULL &&
            mystrcmp(result, expected_path) == 0) {
        printf("PASS: resolved path = \"%s\"\n", result);
    } else {
        printf("FAIL: expected \"%s\", got \"%s\"\n",
            expected_path,
            result != NULL ? result : "NULL");
    }

    printf("\n");


}

int main(void) { 
    /* Test PATH containing standard command directories */ 
    char *env1[] = { "PATH=/bin:/usr/bin", NULL };

    /* Test PATH containing a nonexistent directory */
    char *env3[] = {
        "PATH=/nonexistent",
        NULL
    };

    /* Test environment without PATH */
    char *env4[] = {
        "HOME=/tmp",
        NULL
    };

    run_test(
        "Absolute path",
        "/bin/ls",
        env1,
        "/bin/ls"
    );

    run_test(
        "Relative path",
        "./myprogram",
        env1,
        "./myprogram"
    );

    run_test(
        "Command found in PATH",
        "ls",
        env1,
        "/bin/ls"
    );

    run_test(
        "Command not found in PATH",
        "nonexistent_command_12345",
        env3,
        NULL
    );

    run_test(
        "PATH not found",
        "nonexistent_command_12345",
        env4,
        NULL
    );

    run_test(
        "Empty environment",
        "nonexistent_command_12345",
        NULL,
        NULL
    );

    return 0;


}
