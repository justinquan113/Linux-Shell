#include <unistd.h>
#include "jobs.h"
#include "mystring.h"
#include "prompt.h"
#include "token.h"
#include "myheap.h"
#include "jobs.h"

int get_command(struct Command *command){
    char input[100];
    char *prompt = "$ ";
    char *error = "Please enter a shorter command\n";

    /* loop should only repeat unless user just presses enter or input was invalid */
    while(1){
        free_all();

        /* Write the prompt to console*/
        if (write(1, prompt, mystrlen(prompt)) < 0) {
            print_err_string("write prompt failed");
            return 0;
        }

        /* Read input with full buffer size*/
        ssize_t n = read(0, input, sizeof(input));

        /* Stop on end of input or read error*/
        if (n < 0){
            print_err_string("read input failed");
            command->argc = 0;
            command->argv[0] = 0;
            return 0;
        }

        if (n == 0) {
            command->argc = 0;
            command->argv[0] = 0;
            return 0;
        }

        /* Gives error if user input is too long*/
        if (input[n-1] != '\n'){
            if (write(2, error, mystrlen(error)) < 0) {
                print_err_string("write error failed");
            }
            /*drain the leftover input*/
            char discard;
            while (read(0, &discard, 1) == 1 && discard != '\n');
            continue;
        }

        /* Replace newline with null terminator to properly compare*/
        input[n-1] = '\0';
        
        /* Ignore empty input */
        if (input[0] == '\0'){
            continue;
        }

        command->argc = tokenizer(input, n, command->argv);
        
        /* Check for exit using mystrcmp and break if found,
        to be removed later*/
        if(mystrcmp("exit", input) == 0){
            break;
        }

        break;
    }

    return 1;
}
