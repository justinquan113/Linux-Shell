#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(void){

    char input[30];
    char *prompt = "$ ";
    char *error = "Please enter a shorter command\n";

    while(1){
        /* Write the prompt to console*/
        write(1, prompt, strlen(prompt));

        /* Read input with full buffer size*/
        ssize_t n = read(0, input, sizeof(input));

        /* Stop on end of input or read error*/
        if (n <= 0){
            break;
        }

        /* Gives error if user input is too long*/
        if (input[n-1] != '\n'){
            write(1, error, strlen(error));
            /*drain the leftover input*/
            char discard;
            while (read(0, &discard, 1) == 1 && discard != '\n');
            continue;
        }

        /* Replace newline with null terminator to properly compare*/
        input[n-1] = '\0';

        /* Check for exit using strcmp and break if found,
        to be removed later*/
        if(strcmp("exit", input) == 0){
            break;
        }

        /* Add newline back and then echo input if not exit*/
        input[n - 1] = '\n';
        write(1, input, n);
    }

    return 0;
}
