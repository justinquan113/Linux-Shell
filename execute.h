#ifndef EXECUTE_H
#define EXECUTE_H
#include "jobs.h"

void run_command(struct Command *command, char *envp[], int background);
char *resolve_path(char *command, char*envp[]);
#endif
