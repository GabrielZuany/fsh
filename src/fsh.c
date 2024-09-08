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
        kill_all_processes(global_pmb, signum);
        exit(0);
    }
    printf("Continuing...\n");
    printf("fsh> ");
    fflush(stdout);
    return;
}

void handle_child_signal(int signum) {
    printf("(child) Signal %d received\n", signum);
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (pid > 0) {
        printf("(child) Process %d finished\n", pid);
        fflush(stdout);
    }
    return;
}

int main(int argc, char *argv[]) {
    signal(SIGINT, handle_sigint); // Interrompe
    signal(SIGTERM, handle_signal); // Termina
    signal(SIGSTOP, handle_signal); // Suspende
    signal(SIGCONT, handle_sigcont); // Continua

    global_pmb = create_process_map_block();
    while (true) {
        // clear_process_map_block(global_pmb);
        printf("fsh> ");
        char **commands = read_commands_stdin();
        int i = 0;
        pid_t first_pid = 0;
        for (i = 0; *commands; i++) {
            pid_t pid = fork();
            if (!i) {  first_pid = pid; }

            add_process_to_map_block(global_pmb, pid, *commands);
            char *command = malloc(strlen(*commands) + 1);
            strcpy(command, *commands);

            char **args = get_args_execvp(command);

            if (!i) { // if it's the first command
                if (!pid) { // if it's the child
                    if (execvp(args[0], args) < 0)
                        printf("fsh: command not found\n");
                    exit(0);
                }
                commands++;
                continue; // skip the rest of the loop
            }

            // second command and onwards will be run in the background and create another child
            // remeber the fsh has a built-in bug! The processess create a child process that runs the same command
            if (!pid) { // if it's the child (fsh 2nd/3rd/4th/5th child)
                pid_t bug_pid = fork();
                printf("Bug pid created: %d\n", bug_pid);
                add_process_to_map_block(global_pmb, bug_pid, *commands); // global_pmb should be a shared variable
                if (!bug_pid) { // if it's the (bug) child
                    if (execvp(args[0], args) < 0){
                        printf("fsh: command not found\n");
                    }
                    // fflush(stdout);
                    exit(0);
                }       
                printf("Parent process %d waiting for bug process %d\n----\n", getpid(), bug_pid);
                if (execvp(args[0], args) < 0){
                    printf("fsh: command not found\n");       
                }
                // fflush(stdout);
                exit(0);
            }
            commands++;
        }
        waitpid(first_pid, NULL, WNOHANG); // fsh waits for the child to finish
        fflush(stdout);
    }
    destroy_process_map_block(global_pmb);

    return 0;
}
