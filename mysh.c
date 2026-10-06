#include "string.h"
#include "jobs.h"
#include "execute.h"
#include "prompt.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[]){

  char *newline = "\n";
  int exitShell = 0;
  struct Command command;

  while (!exitShell){
    /* collect any background children that finished since the last prompt */
    while (waitpid(-1, NULL, WNOHANG) > 0){
    }

    command.is_background = 0;
    get_command(&command);

    if (command.argc > 0){

      if(mystrcmp("exit", command.argv[0]) == 0){
        exitShell = 1;
      }

      else{
        if(mystrcmp(command.argv[command.argc - 1], "&") == 0){
          /*flag the shell that this is a background process*/
          command.is_background = 1;

          /*strip the & so the child process doesnt execute it*/
          command.argc--;
          command.argv[command.argc] = 0;
        }

        /*after stripping dont allow a single "&" command to go through*/
        if(command.argc > 0){
          run_command(&command, envp);
          write(1, newline, mystrlen(newline));
        }
      }
    }
  }

  return 0;
}
