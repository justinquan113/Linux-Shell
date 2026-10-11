#include "execute.h"
#include "jobs.h"
#include <unistd.h>
#include "string.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

void run_command(struct Command *command, char *envp[], int background) {
   
    pid_t pid = fork();

    if (pid <0) {
        char *error = "fork did not work in run command\n";
        write(1, error, mystrlen(error));
    }

    else if (pid == 0) {
      
        execve(command->argv[0], command->argv, envp);
    

        char *error = "Error with execve, process should have been replaced\n";
        write (1, error, mystrlen(error));
        _exit(1);
    } 

    else {

        /*skip parent waiting for child process*/
        if(background == 1){
            printf("Background PID: %d\n", pid);
        }

        else{
            waitpid(pid, NULL, 0);
        }
        
       
    }
}
