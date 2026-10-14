#ifndef JOBS_H
#define JOBS_H
#define MAX_PIPELINE_LEN 2
#define MAX_ARGS 10

struct Command
{
  char *argv[MAX_ARGS+1];
  unsigned int argc;
 
};

struct Job
{
  struct Command pipeline[MAX_PIPELINE_LEN];
  unsigned int num_stages;
  char *outfile_path;
  char *infile_path;
  int background;
};

void run_job(struct Job *job, char *envp[]);

/* returns 1 if a job was read, 0 on end of input */
int get_job(struct Job *job);

/* forks and execs one stage; returns the child's pid, or -1 on failure */
int spawn_child_process(struct Command *command, int in_fd, int out_fd, int close_fd, char *envp[]);

#endif
