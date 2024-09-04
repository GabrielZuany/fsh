#include "../libs/pmb.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

struct ProcessMapBlock {
    pid_t* pids;
    char** commands;
    int size;
};

ProcessMapBlock* create_process_map_block() {
    ProcessMapBlock* pmb = malloc(sizeof(ProcessMapBlock));
    pmb->pids = malloc(MAX_COMMANDS * sizeof(pid_t));
    pmb->commands = malloc(MAX_COMMANDS * sizeof(char*));
    pmb->size = 0;
    return pmb;
}

void add_process_to_map_block(ProcessMapBlock* pmb, pid_t pid, char* command) {
    pmb->commands[pmb->size] = command;
    pmb->pids[pmb->size] = pid;
    pmb->size++;
}

void destroy_process_map_block(ProcessMapBlock* pmb) {
    free(pmb->pids);
    free(pmb->commands);
    free(pmb);
}