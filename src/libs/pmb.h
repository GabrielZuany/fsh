#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_PROCESSES 20
#define ALREADY_KILLED -1

typedef struct ProcessMapBlock ProcessMapBlock;

extern ProcessMapBlock *global_pmb;

ProcessMapBlock* create_process_map_block();

void add_process_to_map_block(ProcessMapBlock* pmb, pid_t pid, char* command);

void debug_process_map_block(ProcessMapBlock* pmb);

void kill_all_processes(ProcessMapBlock* pmb, int signum);

void kill_one_process(ProcessMapBlock* pmb, pid_t pid, int signum);

void remove_from_process_map_block(ProcessMapBlock* pmb, pid_t pid);

void clear_process_map_block(ProcessMapBlock* pmb);

void destroy_process_map_block(ProcessMapBlock* pmb);