#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include "libs/lib.h"
#include "libs/pmb.h"

ProcessMapBlock *global_pmb;

void handle_signal(int signum) {
    // Encontrar o processo pai (ou o processo que gerencia os processos filhos)
    // e enviar o sinal a todos os processos filhos.
    printf("Signal %d received\n", signum);
    kill_all_processes(global_pmb, signum);
    exit(0);
}

void handle_sigcont(int signum) {
    printf("Signal %d received\n", signum);
    printf("Continuing from where it was left off...\n");
    fflush(stdout);
    return;
}

void handle_sigint(int signum) {
    printf("Signal %d received\n", signum);
    printf("Do you really want to exit? (y/n) ");
    char c;
    scanf("%c", &c);
    if (c == 'y') {
        printf("Exiting...\n");
        // kill_all_processes(global_pmb, signum);
        exit(0);
    }
    printf("Continuing...\n");
    printf("fsh> ");
    fflush(stdout);
    return;
}

int main(int argc, char *argv[]) {
    signal(SIGINT, handle_sigint); // Interrompe
    signal(SIGTERM, handle_signal); // Termina
    signal(SIGSTOP, handle_signal); // Suspende
    signal(SIGCONT, handle_sigcont); // Continua

    while (true) {
        printf("fsh> ");
        char **commands = read_commands_stdin();
        global_pmb = create_process_map_block();
        for (int i = 0; *commands; i++) {
            pid_t pid = fork();
            add_process_to_map_block(global_pmb, pid, *commands);
            char *command = malloc(strlen(*commands) + 1);
            strcpy(command, *commands);

            char **args = get_args_execvp(command);

            if (!i) { // if it's the first command
                if (!pid) { // if it's the child
                    execvp(args[0], args);
                    exit(0);
                }
                commands++;
                wait(NULL); // wait for the child to finish
                continue; // skip the rest of the loop
            }else{
                // redirect the stdout to /dev/null for the second command and onwards
                int fd = open("/dev/null", O_WRONLY);
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }

            // second command and onwards will be run in the background and create another child
            // remeber the fsh has a built-in bug! The processess create a child process that runs the same command
            strcat(*commands, " &");
            if (!pid) { // if it's the child
                // strcat(*commands, " &");
                execvp(args[0], args);
                exit(0);
            }
            // if it's the parent
            system(*commands);
            commands++;

            wait(NULL);
        }

        // reset the stdout
        int fd = open("/dev/tty", O_WRONLY);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        clear_process_map_block(global_pmb);
        fflush(stdout);
    }
    destroy_process_map_block(global_pmb);

    return 0;
}
