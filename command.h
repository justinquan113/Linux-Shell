#define MAX_ARGS 10

struct Command
{
    char *name;
    char *argv[MAX_ARGS + 1];
    unsigned int argc;
};