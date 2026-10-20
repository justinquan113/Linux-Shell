#include <stdio.h>
#include "jobs.h"

int main(void)
{
    int passed = 0;
    int total = 0;

    struct Command command = {0};
    struct Job job = {0};

    /* Test initial state */
    total++;
    if (command.argc == 0 &&
        command.argv[0] == NULL) {
        printf("PASS: command initialized safely\n");
        passed++;
    } else {
        printf("FAIL: command initialized safely\n");
    }

    /* Test storing arguments */
    command.argv[0] = "/bin/echo";
    command.argv[1] = "hello";
    command.argv[2] = NULL;
    command.argc = 2;

    total++;
    if (command.argc == 2 && command.argv[2] == NULL) {
        printf("PASS: argument count and terminator\n");
        passed++;
    } else {
        printf("FAIL: argument count and terminator\n");
    }

    /* Test initial background state */
    total++;

    if (job.background == 0) 
    { printf("PASS: job initialized in foreground\n"); passed++; } 
    else { 
        printf("FAIL: job initialized in foreground\n"); 
    }

    /* Test background flag */
    job.background = 1;
    total++;
    if (job.background == 1) {
        printf("PASS: job background flag set\n");
        passed++;
    } else {
        printf("FAIL: job background flag set\n");
    }

    printf("\nCommand tests: %d/%d passed\n", passed, total);

    return passed == total ? 0 : 1;
}
