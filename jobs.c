#include "jobs.h"
#include <unistd.h>
#include <stdio.h>
#include "string.h"
#include "token.h"
#include "prompt.h"
int get_job(struct Job *job){

    int success = get_command(&job->pipeline[0]);

    if (!success){
        /* end of input: no job to package */
        job->num_stages = 0;
        return 0;
    }

    job->num_stages = 1;
    job->infile_path = NULL;
    job->outfile_path = NULL;
    job->background = 0;

    return 1;
}

void run_job(struct Job *job, char *envp[]){

}