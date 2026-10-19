#include "parser.h"
#include "jobs.h"
#include "mystring.h"

#define PIPE "|"
#define IN_REDIRECT "<"
#define OUT_REDIRECT ">"
#define BACKGROUND "&"
#define NULL '\0'

/* Take in job struct and parse the pipeline into the job struct. */
/* Currently assumes there will be a space within instructions eg. "ls -l | grep .c"  not "ls -l|grep .c" */
int parse_pipeline(struct Job *job)
{
    struct Command *cmd = &job->pipeline[0];
    char **ptr = cmd->argv;

    job->num_stages = 1;
    job->infile_path = NULL;
    job->outfile_path = NULL;
    job->background = 0;

    char *input_tokens[MAX_ARGS + 1];
    int count = 0;
    int stage = 0;


    /* Copy tokens into temporary array */
    while (*ptr != NULL && count < MAX_ARGS) {
        input_tokens[count++] = *ptr;
        ptr++;
    }

    input_tokens[count] = NULL;

    /* Reset pipeline to initialize commands */
    for (int i = 0; i < MAX_PIPELINE_LEN; i++) {
        job->pipeline[i].argc = 0;
        job->pipeline[i].argv[0] = NULL;
    }

    /* Parse through tokens and appropriately place the commands */
    for (int i = 0; i < count; i++) {
        char *token = input_tokens[i];

        if (mystrcmp(token, PIPE) == 0) {
            if (job->pipeline[stage].argc == 0) {
                return -1;
            }
            if (stage + 1 >= MAX_PIPELINE_LEN) {
                return -1;
            }

            stage++;
            job->num_stages++;
        }
        else if (mystrcmp(token, IN_REDIRECT) == 0) {
            if (i + 1 >= count) {
                return -1;
            }

            job->infile_path = input_tokens[++i];
        }
        else if (mystrcmp(token, OUT_REDIRECT) == 0) {
            if (i + 1 >= count) {
                return -1;
            }

            job->outfile_path = input_tokens[++i];
        }
        else if (mystrcmp(token, BACKGROUND) == 0) {
            job->background = 1;
        }
        else {
            struct Command *current = &job->pipeline[stage];

            if (current->argc >= MAX_ARGS) {
                return -1;
            }

            current->argv[current->argc] = token;
            current->argc++;
            current->argv[current->argc] = NULL;
        }
    }

    /* Check if the last stage has any commands */
    if (job->pipeline[stage].argc == 0) {
        return -1;
    }


    return 0;
}
