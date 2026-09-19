#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(void){
    
    char input[10];
    char *error = "Please enter a shorter command\n";
    char *prompt = "Write Something\n";
    while(1){
        write(1, prompt, strlen(prompt));
        ssize_t n = read(0, input, sizeof(input));
        if (n <= 0){
            break;
        }
        /*Gives error if user input is too long*/
        if (input[n-1] != '\n'){
            write(1, error, strlen(error));
            /*drain the leftover input*/
            char discard;
            while (read(0, &discard, 1) == 1 && discard != '\n');
            continue;
        }
        write(1, input, n);
        input[n-1] = '\0';
        if(strcmp("exit", input) == 0){
            break;
        }

    }
    return 0;
}