#include <unistd.h>
#include "jobs.h"
#include "string.h"
#include "prompt.h"
#include "token.h"
#include "myheap.h"
#include "jobs.h"

void get_command(struct Command *command){
    char input[50];
    char *prompt = "$ ";
    char *error = "Please enter a shorter command\n";

    /* loop should only repeat unless user just presses enter or input was invalid */
    while(1){
        free_all();

        /* Write the prompt to console*/
        write(1, prompt, mystrlen(prompt));

        /* Read input with full buffer size*/
        ssize_t n = read(0, input, sizeof(input));

        /* Stop on end of input or read error*/
        if (n <= 0){
            break;
        }

        /* Gives error if user input is too long*/
        if (input[n-1] != '\n'){
            write(1, error, mystrlen(error));
            /*drain the leftover input*/
            char discard;
            while (read(0, &discard, 1) == 1 && discard != '\n');
            continue;
        }

        /* Replace newline with null terminator to properly compare*/
        input[n-1] = '\0';
        
        // Ignore empty input
        if (input[0] == '\0'){
            continue;
        }

        command->argc = tokenizer(input, n, command->argv);
        
        /* Check for exit using strcmp and break if found,
        to be removed later*/
        if(mystrcmp("exit", input) == 0){
            break;
        }

        break;
    }

}
