#ifndef PROMPT_H
#define PROMPT_H
#include "jobs.h"


/* returns 1 if a command was read, 0 on end of input */
int get_command(struct Command *command);
#endif
