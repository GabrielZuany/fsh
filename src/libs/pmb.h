#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_PROCESSES 200
#define ALREADY_KILLED -1

typedef struct ProcessMapBlock ProcessMapBlock;

/// @brief externally defined global ProcessMapBlock struct -> shared variable
extern ProcessMapBlock *global_pmb;

/// @brief Create a new ProcessMapBlock struct
/// @return ProcessMapBlock* pointer to the new struct
ProcessMapBlock* create_process_map_block();

/// @brief Add a process to the ProcessMapBlock
/// @param pmb ProcessMapBlock* pointer to the struct
/// @param pid pid_t process id
/// @param command char* command
/// @return void
void add_process_to_map_block(ProcessMapBlock* pmb, pid_t pid, char* command);

/// @brief Kill all processes in the ProcessMapBlock
/// @param pmb ProcessMapBlock* pointer to the struct
/// @param signum int signal number
void kill_all_processes(ProcessMapBlock* pmb, int signum);

/// @brief Destroy the ProcessMapBlock struct and free memory
/// @param pmb ProcessMapBlock* pointer to the struct
void destroy_process_map_block(ProcessMapBlock* pmb);