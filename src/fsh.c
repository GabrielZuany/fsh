#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libs/lib.h"

int main(int argc, char *argv[]) {
    while (true) {
        printf("fsh> ");
        char **commands = read_commands_stdin();
        while (*commands) {
            system(*commands);
            commands++;
        }
    }

    return 0;
}
