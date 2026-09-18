#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(void){
    
    char input[100];
    
    char *prompt = "Write Something\n";
    while(1){
        write(1, prompt, strlen(prompt));
        ssize_t n = read(0, input, sizeof(input));
        write(1, input, n);
        input[n-1] = '\0';
        if(strcmp("exit", input) == 0){
            break;
        }
        
    }

    
    
    return 0;
}