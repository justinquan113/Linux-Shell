#include "string.h"
#include "jobs.h"
#include "execute.h"
#include "prompt.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[]){

  int exitShell = 0;
  struct Job job;

  while (!exitShell){
    /* collect any background children that finished since the last prompt */
    while (waitpid(-1, NULL, WNOHANG) > 0){
    }

    
    /* end of input: leave the shell */
    if (!get_job(&job)){
      break;
    }

    if (job.num_stages > 0 && job.pipeline[0].argc > 0){

      if(mystrcmp("exit", job.pipeline->argv[0]) == 0){
        exitShell = 1;
      }

      else{
        run_job(&job, envp);
      }
     
    }
  }
  return 0;
  }


