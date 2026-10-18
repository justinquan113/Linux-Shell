#include "jobs.h"
#include <unistd.h>
#include <stdio.h>
#include "string.h"
#include "token.h"
#include "prompt.h"
#include "execute.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "parser.h"


int get_job(struct Job *job){

    int success = get_command(&job->pipeline[0]);

    if (!success){
        /* end of input: no job to package */
        job->num_stages = 0;
        return 0;
    }

    int parse_result = parse_pipeline(job);

    if (parse_result == -1) {
        return 0;
    }

    return 1;
}

void run_job(struct Job *job, char *envp[]){
    int pipefd[2];
    int pids[MAX_PIPELINE_LEN];
    int num_pids = 0;
    char *err_open = "Error opening the file\n";

    /* default to the shell's own stdin/stdout, then override depending on the job redirections*/
    int in_fd = STDIN_FILENO;
    int out_fd = STDOUT_FILENO;

    if(job->num_stages < 1 || job->num_stages > MAX_PIPELINE_LEN){
        return;
    }

    /*check if there is a infile path in the job*/
    if(job->infile_path != NULL){
        in_fd = open(job->infile_path, O_RDONLY);

        /*error checking for opening a file*/
        if(in_fd < 0){
            write(2, err_open, mystrlen(err_open));
            return;
        }
    }

    /*check if there is a outfile path in the job*/
    if(job->outfile_path != NULL){
        out_fd = open(job->outfile_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

        /*error checking for opening a file*/
        if(out_fd < 0){
            write(2, err_open, mystrlen(err_open));

            if(in_fd != STDIN_FILENO){
                close(in_fd);
            }

            return;
        }
    }

    /* a single command */
    if(job->num_stages == 1){
        int pid = spawn_child_process(&job->pipeline[0], in_fd, out_fd, -1, envp);

        if(pid >= 0){
            pids[num_pids] = pid;
            num_pids++;
        }
    }

    /*n stage pipeline*/
    else{
        char *err_pipe = "Could not create the pipe\n";

        /*saves the previous pipe read end*/
        int prev_read_fd;
        for (unsigned int i = 0; i < job->num_stages; i++){
            int pid;

            /*the last stage writes to out_fd, so it needs no pipe of its own*/
            if(i < job->num_stages - 1){
                if(pipe(pipefd) < 0){
                    write(2, err_pipe, mystrlen(err_pipe));

                    if(in_fd != STDIN_FILENO){
                        close(in_fd);
                    }

                    if(out_fd != STDOUT_FILENO){
                        close(out_fd);
                    }

                    return;
                }
            }
            
            /*First stage always writes*/
            if(i == 0){
                pid = spawn_child_process(&job->pipeline[i], in_fd, pipefd[1], pipefd[0], envp);
                if(pid >= 0){
                    pids[num_pids] = pid;
                    num_pids++;
                }

                /*close write end*/
                close(pipefd[1]);
                /*save the read end for next stage*/
                prev_read_fd = pipefd[0];
            }

            /*Last stage always reads*/
            else if(i == job->num_stages - 1){
                pid = spawn_child_process(&job->pipeline[i], prev_read_fd, out_fd, -1, envp);
                if(pid >= 0){
                    pids[num_pids] = pid;
                    num_pids++;
                }
                /*close read end*/
                close(prev_read_fd);
            }

            /*middle stages read and writes*/
            else{

                pid = spawn_child_process(&job->pipeline[i], prev_read_fd, pipefd[1], pipefd[0], envp);
                if(pid >=0){
                    pids[num_pids] = pid;
                    num_pids++;
                }
                close(prev_read_fd);
                close(pipefd[1]);
                /*save the read end for the next stage*/
                prev_read_fd = pipefd[0];

            }
        }
    }

    /* the children have their own copies now, so drop the parent's */
    if(in_fd != STDIN_FILENO){
        close(in_fd);
    }


    if(out_fd != STDOUT_FILENO){
        close(out_fd);
    }

    /* skip the wait for background jobs; mysh reaps them at the next prompt */
    if(job->background){
        char *background_msg = "Background PID: ";
        char buffer[MYITOA_BUF];

        for(int i = 0; i < num_pids; i++){
            /* myitoa returns where the digits start inside buffer */
            char *digits = myitoa(pids[i], buffer, MYITOA_BUF);

            write(1, background_msg, mystrlen(background_msg));
            write(1, digits, mystrlen(digits));
            write(1, "\n", 1);
        }
    }

    else{
        /* every stage has to be waited on, not just the last */
        for(int i = 0; i < num_pids; i++){
            waitpid(pids[i], NULL, 0);
        }
    }
}

/* forks and execs one stage; returns the child's pid, or -1 on failure.
   the caller decides whether to wait */
int spawn_child_process(struct Command *command, int in_fd, int out_fd, int close_fd, char *envp[]){
    char *err = "fork failed\n";

    int pid = fork();

    if(pid < 0){
        write(2, err, mystrlen(err));
        return -1;
    }

    else if(pid == 0){

        /*redirect the infile fd to stdin*/
        if(in_fd != STDIN_FILENO){
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }

        /*redirect the outfile fd to stdout*/
        if(out_fd != STDOUT_FILENO){
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }

        /*close pipe end that is not being used*/
        if(close_fd >= 0){
            close(close_fd);
        }

        if (command->argv[0][0] != '/' && command->argv[0][0] != '.') {
            char *resolved = resolve_path(command->argv[0], envp);

            /*nothing on PATH matched, so there is no point calling execve*/
            if (resolved == 0) {
                char *not_found = ": command not found\n";

                write(2, command->argv[0], mystrlen(command->argv[0]));
                write(2, not_found, mystrlen(not_found));
                _exit(127);
            }

            command->argv[0] = resolved;
        }
        execve(command->argv[0], command->argv, envp);

        char *error = "Error with execve, process should have been replaced\n";
        write (2, error, mystrlen(error));
        _exit(1);
    }

    return pid;
}


