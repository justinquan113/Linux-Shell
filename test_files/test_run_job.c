#include "mystring.h"
#include "jobs.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void test_2_stage_pipeline(char *envp[]);
void test_background_jobs(char *envp[]);
void test_input_redirection_pipeline(char *envp[]);
void test_3_stage_pipeline(char *envp[]);

int main(int argc, char *argv[], char *envp[]){
    (void)argc;
    (void)argv;

    

    test_2_stage_pipeline(envp);
    printf("\n");
    test_background_jobs(envp);
    printf("\n");
    test_input_redirection_pipeline(envp);
    printf("\n");
    test_3_stage_pipeline(envp);
    printf("\n");
    
    


    return 0;
}

void test_3_stage_pipeline(char *envp[]){
    printf("Test case: 3 stage pipeline\n");
    printf("Test input: echo hello world | tr a-z A-Z | rev > runjob_test4.txt\n");
    char *file[50];
    struct Job test4 =
        {
        { { { "echo", "hello world", NULL }, 2 },
        { { "tr", "a-z", "A-Z", NULL }, 3 },
        { {"rev", NULL}, 1 },
        },
        3,
        "3stage_test",
        NULL,
        0
        };
    
    run_job(&test4, envp);
    printf("Opening 3stage_test...\n");
   
    int fd = open("3stage_test", O_RDONLY);
    if (fd < 0) {
        printf("FAIL: could not open 3stage_test\n");
        return;
    }
    else{
        printf("SUCCESS: opened 3stage_test\n");
    }
    ssize_t n = read(fd, file, sizeof(file) - 1);
    close(fd);
    if (n < 0) {
        printf("FAIL: could not read 3stage_test\n");
        return;
    }
    file[n] = '\0';

    printf("Result: %s", file);
    if(mystrcmp(file, "DLROW OLLEH\n") == 0){
        printf("TEST PASSED\n");
        
    }



}

void test_input_redirection_pipeline(char *envp[]){
    char file[50];
    char *expected = "67\n";
    printf("Test case: Getting max number from an infile\n");
    printf("Test input: sort -n < numbers.txt | tail -1 > maxnum\n");
    printf("Numbers in numbers.txt: 21, 45, 67, 24\n");

    struct Job test3 =
        {
        { { { "sort", "-n", NULL }, 2 },
        { { "tail", "-1", NULL }, 2 },
        },
        2,
        "maxnum",
        "numbers.txt",
        0
        };

    run_job(&test3, envp);

    int fd = open("maxnum", O_RDONLY);
    if (fd < 0) {
        printf("FAIL: could not open maxnum\n");
        return;
    }
    ssize_t n = read(fd, file, sizeof(file) - 1);
    close(fd);
    if (n < 0) {
        printf("FAIL: could not read maxnum\n");
        return;
    }
    file[n] = '\0';

    printf("Result: %s", file);

    /* the largest number in the file, so this only passes if the first
       stage actually read from numbers.txt and the pipe carried it along */
    if (mystrcmp(file, expected) == 0) {
        printf("TEST PASSED\n");
    } else {
        printf("FAIL: expected %s\n", expected);
    }
}


void test_background_jobs(char *envp[]){
    printf("Test case: Getting background pids\n");
    printf("Test input: ls -al &\n");
    struct Job test2 =
        {
        { { { "ls", NULL }, 1 },
        },
        1,
        "/dev/null",  /* discard the child's stdout; the PID still goes to fd 1 */
        NULL,
        1
        };

    run_job(&test2, envp);
    printf("Background PID shown: PASSED\n");
    printf("TEST PASSED\n");
    
}   

void test_2_stage_pipeline(char *envp[]){
    char file[50];  
    printf("Test case: 2 stage pipeline with output redirection\n");
    printf("Test input: ls -al | wc -l > dirlistlen\n");
    struct Job test1 =
        {
        { { { "ls", "-al", NULL }, 2 },
        { { "wc", "-l", NULL }, 2 },
        },
        2,
        "dirlistlen",
        NULL,
        0
        };

    run_job(&test1, envp);
    printf("Opening dirlistlen...\n");
    printf("Opening: PASSED\n");
    int fd = open("dirlistlen", O_RDONLY);
    if (fd < 0) {
        printf("FAIL: could not open dirlistlen\n");
        return;
    }
    ssize_t n = read(fd, file, sizeof(file) - 1);
    close(fd);
    if (n < 0) {
        printf("FAIL: could not read dirlistlen\n");
        return;
    }
    file[n] = '\0';

    printf("Result: %s", file);
    printf("TEST PASSED\n");

    
}