#include <stdio.h>
#include <string.h>
#include "prompt.h"
#include "token.h"

void run_test(const char *test_name, const char *test_input) {
    char input_buffer[50];
    char *tokens[MAX_TOKENS + 1];
    int i;

    /* Copy the test input into a buffer*/
    strncpy(input_buffer, test_input, sizeof(input_buffer) -1);
    input_buffer[sizeof(input_buffer) -1] = '\0';

    int length = strlen(input_buffer);

    printf("Test case: %s\n", test_name);
    printf("Test input: %s\n", test_input);

    int num_tokens = tokenizer(input_buffer, length + 1, tokens);

    printf("Token count: %d\n", num_tokens);
    for (i = 0; i < num_tokens; i++) {
        printf("Token[%d]: \"%s\"\n", i, tokens[i]);
    }
}

int main (void) {
    run_test("Normal String oh yeah", "rm  -i /pnove300/comp3659/readings");

    return 0;
}
