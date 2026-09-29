#include "token.h"
#include "string.h"
#include <unistd.h>
#include "myheap.h"

int tokenizer(char input[], int size, char *tokens[]){

    int numTokens = 0;
    char *start_token = 0;
    for (int i = 0; i < size; i++){
        
        /*indicates this is the end of the token*/
        if(input[i] == ' ' || input[i] == '\n' || input[i] == '\0'){

            if (start_token == 0) {
                continue;
            }
            input[i] = '\0';
            
            // get size of individual token
            unsigned int len = mystrlen(start_token);

            // include extra space for null terminator
            char *token = alloc(len + 1);

            if (token != 0) {
                if (numTokens < MAX_TOKENS) {
                    mystrcpy(token, start_token);
                    tokens[numTokens] = token;
                    numTokens++;
                }
            }

            start_token = 0;
        }
        /*start of new token*/
        else if(!start_token){
            start_token = &input[i];
        }

    }
    return numTokens;
}
        
 