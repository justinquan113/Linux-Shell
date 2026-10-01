#include "string.h"
#include "jobs.h"
#include "execute.h"
#include "prompt.h"

int main(int argc, char *argv[], char *envp[])
{
  int exitShell = 0;
  struct Command command;

  
  while (!exitShell)
  {
    get_command(&command);
    if (command.argc > 0)
      {
        if (mystrcmp("exit", command.argv[0]) == 0)
          {
              exitShell = 1;
            }
          else
            {
              run_command(&command, envp);
            }
        }
    }

  return 0;
}
