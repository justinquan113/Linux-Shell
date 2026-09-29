#include "execute.h"
#include "jobs.h"
#include <unistd.h>

void run_command(struct Command *command) {
    
    pid_t pid = fork();

    if (pid <0) {
        return 1;
    }
    if (pid == 0) {
        execve()
    }
}