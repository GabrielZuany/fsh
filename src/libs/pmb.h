#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_COMMANDS 10

typedef struct ProcessMapBlock ProcessMapBlock;

ProcessMapBlock* create_process_map_block();

void add_process_to_map_block(ProcessMapBlock* pmb, pid_t pid, char* command);

void kill_all_processes(ProcessMapBlock* pmb, int signum);

void clear_process_map_block(ProcessMapBlock* pmb);

void destroy_process_map_block(ProcessMapBlock* pmb);