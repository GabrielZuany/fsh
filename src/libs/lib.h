#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMANDS 5
#define MAX_ARGS 2

char **read_commands_stdin();

char **get_args_execvp(char *command);
