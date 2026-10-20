#include <stdio.h>
#include "mystring.h"
#include "token.h"
#include "myheap.h"

void run_test(
    const char *test_name,
    const char *test_input,
    int expected_count,
    const char *expected_tokens[]
) {
    char input_buffer[50];
    char *tokens[MAX_TOKENS + 1] = {0};
    int passed = 1;

    /* Reset memory before each test */
    free_all();

    /* Copy input safely */
    size_t length = mystrlen(test_input);

    if (length >= sizeof(input_buffer)) {
        printf("FAIL: %s - input too long for test buffer\n\n",
               test_name);
        return;
    }

    mystrcpy(input_buffer, test_input);

    printf("Test case: %s\n", test_name);
    printf("Test input: \"%s\"\n", test_input);

    int num_tokens = tokenizer(
        input_buffer,
        (int)length + 1,
        tokens
    );

    /* Check argument count */
    if (num_tokens != expected_count) {
        printf("FAIL: expected %d tokens, got %d\n",
               expected_count, num_tokens);
        passed = 0;
    }

    /* Check individual tokens */
    if (num_tokens == expected_count) {
        for (int i = 0; i < expected_count; i++) {
            if (tokens[i] == NULL ||
                mystrcmp(tokens[i], expected_tokens[i]) != 0) {
                printf("FAIL: token %d incorrect\n", i);
                passed = 0;
            } else {
                printf("PASS: token %d = \"%s\"\n",
                       i, tokens[i]);
            }
        }
    }

    /* Check argv NULL terminator */
    if (num_tokens >= 0 &&
        num_tokens <= MAX_TOKENS &&
        tokens[num_tokens] == NULL) {
        printf("PASS: argv is NULL-terminated\n");
    } else {
        printf("FAIL: argv is not safely NULL-terminated\n");
        passed = 0;
    }

    printf("%s: %s\n\n",
           passed ? "RESULT" : "RESULT",
           passed ? "PASS" : "FAIL");
}

int main(void) {
    const char *test1[] = {
        "rm", "-i", "/pnove300/comp3659/readings"
    };

    const char *test2[] = {"ls"};

    const char *test3[] = {"ls", "-l"};

    const char *test4[] = {"echo", "hello", "world"};

    const char *test5[] = {"echo", "&"};

    const char *test6[] = {"cat", "file.txt", "|", "wc", "-l"};

    const char *test7[] = {"sort", "<", "input.txt", ">", "output.txt"};

    const char *test8[] = {"echo", "hello", "&"};

    run_test(
        "Normal command",
        "rm -i /pnove300/comp3659/readings",
        3, test1
    );

    run_test("Single token", "ls", 1, test2);

    run_test("Repeated spaces", "ls   -l", 2, test3);

    run_test("Multiple arguments", "echo hello world",
             3, test4);

    run_test("Background marker", "echo &", 2, test5);

    run_test("Empty input", "", 0, NULL);

    run_test("Pipeline", "cat file.txt | wc -l", 5, test6);

    run_test("Input and output redirection", "sort < input.txt > output.txt", 5, test7);

    run_test("Background marker with arguments", "echo hello &", 3, test8);
    
    return 0;
}
