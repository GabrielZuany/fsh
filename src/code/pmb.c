#include "../libs/pmb.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

struct ProcessMapBlock {
    pid_t* pids;
    char** commands;
    int size;
};

ProcessMapBlock* create_process_map_block() {
    ProcessMapBlock* pmb = malloc(sizeof(ProcessMapBlock));
    pmb->pids = malloc(MAX_PROCESSES * sizeof(pid_t));
    pmb->commands = malloc(MAX_PROCESSES * sizeof(char*));
    pmb->size = 0;
    return pmb;
}

void add_process_to_map_block(ProcessMapBlock* pmb, pid_t pid, char* command) {
    pmb->commands[pmb->size] = command;
    pmb->pids[pmb->size] = pid;
    pmb->size++;
}

void debug_process_map_block(ProcessMapBlock* pmb) {
    printf("ProcessMapBlock: %p\n", pmb);
    printf("Size: %d\n", pmb->size);
    for (int i = 0; i < pmb->size; i++) {
        printf("PID: %d\n", pmb->pids[i]);
        printf("Command: %s\n---\n", pmb->commands[i]);
    }
}

void remove_from_process_map_block(ProcessMapBlock* pmb, pid_t pid) {
    if (pmb == NULL) {
        return;
    }
    for (int i = 0; i < pmb->size; i++) {
        if (pmb->pids[i] == pid) {
            pmb->pids[i] = ALREADY_KILLED;
            return;
        }
    }
}

void kill_one_process(ProcessMapBlock* pmb, pid_t pid, int signum) {
    if (pmb == NULL) {
        return;
    }
    for (int i = 0; i < pmb->size; i++) {
        if (pmb->pids[i] == pid) {
            printf("Killing process %d :::: %s\n", pmb->pids[i], pmb->commands[i]);
            kill(pmb->pids[i], signum);
            pmb->pids[i] = ALREADY_KILLED;
            return;
        }
    }
    printf("Process %d not found\n", pid);
}

void kill_all_processes(ProcessMapBlock* pmb, int signum) {
    printf("Killing all processes\n");
    if (pmb == NULL){ return;}
    int count = 0;
    int i = 0;
    for (i = 0; i < pmb->size; i++) {
        if (pmb->pids[i] == ALREADY_KILLED) {
            continue;
        }
        /* if (kill(pmb->pids[i], signum) == 0) { */
            printf("Killing process %d :::: %s\n", pmb->pids[i], pmb->commands[i]);
            kill(pmb->pids[i], signum);
            remove_from_process_map_block(pmb, pmb->pids[i]);
        /* } */
        count++;
    }
    if (count == 0) {
        printf("No processes to kill\n");
    } else {
        printf("Killed %d processes\n", count);
    }
}

void destroy_process_map_block(ProcessMapBlock* pmb) {
    free(pmb->pids);
    free(pmb->commands);
    free(pmb);
}

void clear_process_map_block(ProcessMapBlock* pmb) {
    for (int i = 0; i < pmb->size; i++) {
        pmb->pids[i] = 0;
        // free(pmb->commands[i]);
    }
    pmb->size = 0;
}
