#include <unistd.h>
#include <string.h>

int main(void){
    char *prompt = "Write Something\n";
    char input[100];
    write(1, prompt, strlen(prompt));
    
    ssize_t n = read(0, input, sizeof(input));

    write(1, input, n);
    
    return 0;
}