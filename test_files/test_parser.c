#include <stdio.h>
#include "mystring.h"
#include "jobs.h"
#include "parser.h"

int passed = 0;
int total = 0;


/* Print an individual check */
void check_value(const char *description, int condition)
{
    if (condition) {
        printf("PASS: %s\n", description);
    } else {
        printf("FAIL: %s\n", description);
    }
}


/* Set up input tokens in the first command */
void setup_tokens(struct Job *job,
                  const char *input_tokens[],
                  int count)
{
    job->pipeline[0].argc = count;

    for (int i = 0; i < count; i++) {
        job->pipeline[0].argv[i] = (char *)input_tokens[i];
    }

    job->pipeline[0].argv[count] = NULL;
}


/* Print the input tokens */
void print_input(const char *tokens[], int count)
{
    printf("Test input: \"");

    for (int i = 0; i < count; i++) {
        printf("%s%s", tokens[i], i < count - 1 ? " " : "");
    }

    printf("\"\n");
}


/* Print the parsed pipeline */
void print_pipeline(const struct Job *job)
{
    for (unsigned int stage = 0;
         stage < job->num_stages && stage < MAX_PIPELINE_LEN;
         stage++) {

        const struct Command *command = &job->pipeline[stage];

        printf("Stage %u:\n", stage);

        for (unsigned int i = 0;
             i < command->argc && i < MAX_ARGS;
             i++) {

            if (command->argv[i] != NULL) {
                printf("PASS: stage %u argv[%u] = \"%s\"\n",
                       stage, i, command->argv[i]);
            } else {
                printf("FAIL: stage %u argv[%u] is NULL unexpectedly\n",
                       stage, i);
            }
        }

        if (command->argc <= MAX_ARGS &&
            command->argv[command->argc] == NULL) {
            printf("PASS: stage %u argv is NULL-terminated\n", stage);
        } else {
            printf("FAIL: stage %u argv is not NULL-terminated\n", stage);
        }

        printf("PASS: stage %u argc = %u\n", stage, command->argc);
    }

    printf("Number of stages: %u\n", job->num_stages);
    printf("Input file: %s\n",
           job->infile_path ? job->infile_path : "NULL");
    printf("Output file: %s\n",
           job->outfile_path ? job->outfile_path : "NULL");
    printf("Background: %d\n", job->background);
}


/* Finish a test and print its result */
void finish_test(const char *name, int condition)
{
    printf("%s\n", name);
    if (condition) {
        printf("RESULT: PASS\n");
        passed++;
    } else {
        printf("RESULT: FAIL\n");
    }

    total++;
}


/* Test a single command */
void test_single_command(void)
{
    struct Job job = {0};
    const char *tokens[] = {"ls", "-l"};

    printf("\nTest case: Single command\n");
    print_input(tokens, 2);

    setup_tokens(&job, tokens, 2);

    int result = parse_pipeline(&job);

    check_value("parser returned success", result == 0);

    if (result == 0) {
        print_pipeline(&job);
    }

    int success =
        result == 0 &&
        job.num_stages == 1 &&
        job.pipeline[0].argc == 2 &&
        mystrcmp(job.pipeline[0].argv[0], "ls") == 0 &&
        mystrcmp(job.pipeline[0].argv[1], "-l") == 0 &&
        job.pipeline[0].argv[2] == NULL;

    finish_test("Single command", success);
}


/* Test two commands separated by a pipe */
void test_two_commands(void)
{
    struct Job job = {0};
    const char *tokens[] = {"cat", "file.txt", "|", "wc", "-l"};

    printf("\nTest case: Two-command pipeline\n");
    print_input(tokens, 5);

    setup_tokens(&job, tokens, 5);

    int result = parse_pipeline(&job);

    check_value("parser returned success", result == 0);

    if (result == 0) {
        print_pipeline(&job);
    }

    int success =
        result == 0 &&
        job.num_stages == 2 &&
        job.pipeline[0].argc == 2 &&
        mystrcmp(job.pipeline[0].argv[0], "cat") == 0 &&
        mystrcmp(job.pipeline[0].argv[1], "file.txt") == 0 &&
        job.pipeline[0].argv[2] == NULL &&
        job.pipeline[1].argc == 2 &&
        mystrcmp(job.pipeline[1].argv[0], "wc") == 0 &&
        mystrcmp(job.pipeline[1].argv[1], "-l") == 0 &&
        job.pipeline[1].argv[2] == NULL;

    finish_test("Two-command pipeline", success);
}


/* Test that too many pipeline stages are accepted */
void test_three_commands(void)
{
    struct Job job = {0};
    const char *tokens[] = {
        "cat", "file.txt", "|",
        "grep", "hello", "|",
        "wc", "-l"
    };

    printf("\nTest case: Three command stage\n");
    print_input(tokens, 8);

    setup_tokens(&job, tokens, 8);

    int result = parse_pipeline(&job);

    check_value("parser accepts three pipeline stages", result == 0);

    if (result == 0) {
        print_pipeline(&job);
    }

    int success =
        result == 0 &&
        job.num_stages == 3 &&
        job.pipeline[0].argc == 2 &&
        mystrcmp(job.pipeline[0].argv[0], "cat") == 0 &&
        mystrcmp(job.pipeline[0].argv[1], "file.txt") == 0 &&
        job.pipeline[0].argv[2] == NULL &&
        job.pipeline[1].argc == 2 &&
        mystrcmp(job.pipeline[1].argv[0], "grep") == 0 &&
        mystrcmp(job.pipeline[1].argv[1], "hello") == 0 &&
        job.pipeline[1].argv[2] == NULL &&
        job.pipeline[2].argc == 2 &&
        mystrcmp(job.pipeline[2].argv[0], "wc") == 0 &&
        mystrcmp(job.pipeline[2].argv[1], "-l") == 0 &&
        job.pipeline[2].argv[2] == NULL;

    finish_test("Three-command pipeline", success);

}


/* Test input redirection */
void test_input_redirection(void)
{
    struct Job job = {0};
    const char *tokens[] = {"sort", "<", "input.txt"};

    printf("\nTest case: Input redirection\n");
    print_input(tokens, 3);

    setup_tokens(&job, tokens, 3);

    int result = parse_pipeline(&job);

    check_value("parser returned success", result == 0);

    if (result == 0) {
        print_pipeline(&job);
    }

    int success =
        result == 0 &&
        job.infile_path != NULL &&
        mystrcmp(job.infile_path, "input.txt") == 0 &&
        job.pipeline[0].argc == 1 &&
        mystrcmp(job.pipeline[0].argv[0], "sort") == 0;

    finish_test("Input redirection", success);
}


/* Test output redirection */
void test_output_redirection(void)
{
    struct Job job = {0};
    const char *tokens[] = {"echo", "hello", ">", "output.txt"};

    printf("\nTest case: Output redirection\n");
    print_input(tokens, 4);

    setup_tokens(&job, tokens, 4);

    int result = parse_pipeline(&job);

    check_value("parser returned success", result == 0);

    if (result == 0) {
        print_pipeline(&job);
    }

    int success =
        result == 0 &&
        job.outfile_path != NULL &&
        mystrcmp(job.outfile_path, "output.txt") == 0 &&
        job.pipeline[0].argc == 2 &&
        mystrcmp(job.pipeline[0].argv[0], "echo") == 0 &&
        mystrcmp(job.pipeline[0].argv[1], "hello") == 0;

    finish_test("Output redirection", success);
}


/* Test background marker */
void test_background(void)
{
    struct Job job = {0};
    const char *tokens[] = {"sleep", "5", "&"};

    printf("\nTest case: Background command\n");
    print_input(tokens, 3);

    setup_tokens(&job, tokens, 3);

    int result = parse_pipeline(&job);

    check_value("parser returned success", result == 0);

    if (result == 0) {
        print_pipeline(&job);
    }

    int success =
        result == 0 &&
        job.background == 1 &&
        job.pipeline[0].argc == 2 &&
        mystrcmp(job.pipeline[0].argv[0], "sleep") == 0 &&
        mystrcmp(job.pipeline[0].argv[1], "5") == 0;

    finish_test("Background command", success);
}


/* Test foreground defaults */
void test_foreground_defaults(void)
{
    struct Job job = {0};
    const char *tokens[] = {"echo", "hello"};

    printf("\nTest case: Foreground defaults\n");
    print_input(tokens, 2);

    setup_tokens(&job, tokens, 2);

    int result = parse_pipeline(&job);

    check_value("parser returned success", result == 0);

    if (result == 0) {
        print_pipeline(&job);
    }

    int success =
        result == 0 &&
        job.background == 0 &&
        job.infile_path == NULL &&
        job.outfile_path == NULL;

    finish_test("Foreground defaults", success);
}


/* Test a pipe with no command after it */
void test_trailing_pipe(void)
{
    struct Job job = {0};
    const char *tokens[] = {"cat", "|"};

    printf("\nTest case: Trailing pipe\n");
    print_input(tokens, 2);

    setup_tokens(&job, tokens, 2);

    int result = parse_pipeline(&job);

    check_value("parser rejects trailing pipe", result != 0);

    finish_test("Reject trailing pipe", result != 0);
}


/* Test consecutive pipes */
void test_consecutive_pipes(void)
{
    struct Job job = {0};
    const char *tokens[] = {"cat", "|", "|", "wc"};

    printf("\nTest case: Consecutive pipes\n");
    print_input(tokens, 4);

    setup_tokens(&job, tokens, 4);

    int result = parse_pipeline(&job);

    check_value("parser rejects consecutive pipes", result != 0);

    finish_test("Reject consecutive pipes", result != 0);
}


/* Test missing redirection filename */
void test_missing_filename(void)
{
    struct Job job = {0};
    const char *tokens[] = {"cat", "<"};

    printf("\nTest case: Missing input filename\n");
    print_input(tokens, 2);

    setup_tokens(&job, tokens, 2);

    int result = parse_pipeline(&job);

    check_value("parser rejects missing filename", result != 0);

    finish_test("Reject missing input filename", result != 0);
}


/* Run all tests */
int main(void)
{
    test_single_command();
    test_two_commands();
    test_three_commands();
    test_input_redirection();
    test_output_redirection();
    test_background();
    test_foreground_defaults();
    test_trailing_pipe();
    test_consecutive_pipes();
    test_missing_filename();

    printf("\nParser tests: %d/%d passed\n", passed, total);

    return passed == total ? 0 : 1;
}