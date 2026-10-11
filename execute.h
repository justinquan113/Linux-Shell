#ifndef EXECUTE_H
#define EXECUTE_H
#include "jobs.h"

void run_command(struct Command *command, char *envp[], int background);

#endif
