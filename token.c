#include "token.h"
#include "string.h"
#include <unistd.h>
int tokenizer(char input[], int size, char *tokens[]){

    int numTokens = 0;
    int in_token = 0;
    for (int i = 0; i < size; i++){
        
        /*indicates this is the end of the token*/
        if(input[i] == ' ' || input[i] == '\n'){
            input[i] = '\0';
            in_token = 0;

        }
        /*start of new token*/
        else if(!in_token){
            tokens[numTokens] = &input[i];
            numTokens++;
            in_token = 1;
        }

    }
    return numTokens;
}
        
 