#include "../libs/lib.h"
#include <string.h>

char **read_commands_stdin() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, stdin);
    if (read == -1) {
        return NULL;
    }

    char **commands = malloc(MAX_COMMANDS * sizeof(char *));
    int i = 0;
    for (char *c = strtok(line, "#"); c; c = strtok(NULL, "#")) {
        commands[i] = malloc(strlen(c) + 1);
        if (c[0] == ' ')
            c++;
        if (c[strlen(c) - 1] == '\n')
            c[strlen(c) - 1] = '\0';
        commands[i++] = c;
    }

    return commands;
}
