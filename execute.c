#include "execute.h"
#include "jobs.h"
#include <unistd.h>
#include "string.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "myheap.h"

char *resolve_path(char *command, char*envp[]) {

    if (command[0] == '/' || command[0] == '.') {
        return command;
    }

    char *path = 0;
    if (envp != 0) {
        for (int i = 0; envp[i] != 0; i++) {
            if (envp[i][0] == 'P' && envp[i][1] == 'A'  && envp[i][2] == 'T'
                && envp[i][3] == 'H' && envp[i][4] == '=') {
                    path = envp[i] + 5; // *path will now point to the string after PATH=
                }
        }
    }

    // just in case PATH= is not found, this is the default
    if (path == 0) {
        path = "/bin";
    }

    unsigned int path_len = mystrlen(path);
    char *path_copy = alloc(path_len + 1);
    
    mystrcpy(path_copy, path);

    char *directory = path_copy;
    unsigned int command_len = mystrlen(command);

    for (unsigned int i = 0; i <= path_len; i++) {
        if (path_copy[i] == ':' || path_copy[i] == '\0') {
            path_copy[i] = '\0'; // separate by \0 instead of :

            if (directory[0] != '\0') {
                unsigned int directory_len = mystrlen(directory);

                // +2 to make space for / and \0
                char *final_path = alloc(directory_len + command_len + 2);
                if (final_path != 0) {
                    mystrcat(final_path, directory);
                    mystrcat(final_path, "/");
                    mystrcat(final_path, command);

                    if (access(final_path, X_OK) == 0) {
                        return final_path;
                    }
                }
            }

            directory = &path_copy[i + 1];
        }
    }

    return 0;
}

