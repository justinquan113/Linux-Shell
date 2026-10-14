#include "jobs.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "string.h"
int main(int argc, char *argv[], char *envp[]){
    struct Job job;
    char *expected = "Expected Result: ";
    char *actual = "Actual Result: ";
    char file[50];

    struct Job eg2 =
        {
        { { { "/bin/ls", "-al", "/library", NULL }, 3 },
        { { "/usr/bin/wc", "-l", NULL }, 2 }
        },
        2,
        "dirlistlen",
        NULL,
        0
        };


    run_job(&eg2, envp);
    int fd = open("dirlistlen", O_RDONLY);

    ssize_t n = read(fd, file, sizeof(file));
    write(1, expected, mystrlen(expected));
    
    write(1, "\n", 1);
    write(1, actual, mystrlen(actual));
    write(1, file, mystrlen(file));
    write(1, "\n", 1);
    
    close(fd);
   

    return 0;
}
