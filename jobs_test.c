#include "jobs.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "mystring.h"
int main(int argc, char *argv[], char *envp[]){
    
    char *expected = "Expected Result: ";
    char *actual = "Actual Result: ";
    char file[50];  
    char *t3 = "TEST 3: ";
    char *t2 = "Test 2: ";
    char *test2 = "ls -al /library | wc -l > dirlistlen";
    char *test3 = "ls -al bin | grep bin | wc -l > dirlistlen\n";
    char *test2_result = "68";
    char *test3_result = "17";
    struct Job eg2 =
        {
        { { { "ls", "-al", "/library", NULL }, 3 },
        { { "wc", "-l", NULL }, 2 }
        },
        2,
        "dirlistlen",
        NULL,
        1
        };


    /* /bin/ls -al /usr/bin | /usr/bin/grep bin | /usr/bin/wc -l > dirlistlen */
    struct Job eg3 =
        {
        { { { "ls", "-al", "/usr/bin", NULL }, 3 },
        { { "/usr/bin/grep", "bin", NULL }, 2 },
        { { "/usr/bin/wc", "-l", NULL }, 2 }
        },
        3,
        "dirlistlen",
        NULL,
        1
        };

    /* an input file the test owns, so the expected count comes from how it
       was built rather than from whatever happens to be on this machine.
       3 of the 5 lines contain "bin" */

    int in = open("eg4_in.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    write(in, eg4_input, mystrlen(eg4_input));
    close(in);

    /* /usr/bin/grep bin < eg4_in.txt | /usr/bin/sort | /usr/bin/wc -l > dirlistlen */
    struct Job eg4 =
        {
        { { { "/usr/bin/grep", "bin", NULL }, 2 },
        { { "/usr/bin/sort", NULL }, 1 },
        { { "/usr/bin/wc", "-l", NULL }, 2 }
        },
        3,
        "dirlistlen",
        "eg4_in.txt",
        0
        };

    run_job(&eg3, envp);
    int fd = open("dirlistlen", O_RDONLY);

    ssize_t n = read(fd, file, sizeof(file) - 1);

    /* read does not terminate the buffer, so mystrlen would run off the end */
    if (n < 0){
        n = 0;
    }
    file[n] = '\0';
    
   

    /*3 stage test*/
    write(1, t3, mystrlen(t3));
    write(1, test3, mystrlen(test3));
    write(1, expected, mystrlen(expected));
    write(1, test3_result, mystrlen(test3_result));
    write(1, "\n", 1);
    write(1, actual, mystrlen(actual));
    write(1, file, mystrlen(file));
    write(1, "\n", 1);

    close(fd);
   

    return 0;
}
