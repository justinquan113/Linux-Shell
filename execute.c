#include "execute.h"
#include "jobs.h"
#include <unistd.h>
#include "string.h"
#include <sys/types.h>
#include <sys/wait.h>

void run_command(struct Command *command, char *envp[]) {
   
    pid_t pid = fork();

    if (pid <0) {
        char *error = "fork did not work in run command\n";
        write(1, error, mystrlen(error));
    }

    if (pid == 0) {
        execve(command->argv[0], command->argv, envp);
    

        char *error = "Error with execve, process should have been replaced\n";
        write (1, error, mystrlen(error));
        _exit(1);
    } else {
        waitpid(pid, NULL, 0);
    }
}
