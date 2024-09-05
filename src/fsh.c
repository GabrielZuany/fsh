#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libs/lib.h"
#include "libs/pmb.h"

int main(int argc, char *argv[]) {
    while (true) {
        printf("fsh> ");
        char **commands = read_commands_stdin();
        ProcessMapBlock *pmb = create_process_map_block();
        for (int i = 0; *commands; i++) {
            pid_t pid = fork();
            add_process_to_map_block(pmb, pid, *commands);
            
            if (!i) {
                if (!pid) {
                    system(*commands);
                    exit(0);
                }
                commands++;
                wait(NULL);
                continue;
            }
            
            if (!pid) {
                strcat(*commands, " &");
                system(*commands);
                // create another child and run the same command
                // the command running in background terminates after the parent prints the prompt
                // change system to exec ?
                exit(0);
            }
            commands++;

            wait(NULL);
        }
    }

    return 0;
}
