#include "../libs/pmb.h"    
#include <string.h>         
#include <stdbool.h>        
#include <stdio.h>          
#include <stdlib.h>         
#include <unistd.h>         
#include <sys/types.h>      
#include <signal.h>         

// Define a structure to hold process-related information
struct ProcessMapBlock {
    pid_t* pids;             // Array of process IDs
    char** commands;         // Array of command strings associated with processes
    int size;               // Number of processes currently being tracked
};

// Function to create and initialize a ProcessMapBlock structure
ProcessMapBlock* create_process_map_block() {
    ProcessMapBlock* pmb = malloc(sizeof(ProcessMapBlock));  // Allocate memory for ProcessMapBlock
    pmb->pids = malloc(MAX_PROCESSES * sizeof(pid_t));        // Allocate memory for process IDs array
    pmb->commands = malloc(MAX_PROCESSES * sizeof(char*));    // Allocate memory for commands array
    pmb->size = 0;                                            // Initialize size to 0
    return pmb;                                               // Return the newly created ProcessMapBlock
}

// Function to add a process to the ProcessMapBlock
void add_process_to_map_block(ProcessMapBlock* pmb, pid_t pid, char* command) {
    pmb->commands[pmb->size] = command;  // Add the command to the commands array
    pmb->pids[pmb->size] = pid;         // Add the process ID to the pids array
    pmb->size++; 
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

// Function to kill all processes tracked by the ProcessMapBlock
void kill_all_processes(ProcessMapBlock* pmb, int signum) {
    if (pmb == NULL) { return; }
    
    printf("Killing all processes\n");
    int count = 0;  // Counter for the number of processes killed
    int i = 0;
    for (i = 0; i < pmb->size; i++) {
        if (pmb->pids[i] == ALREADY_KILLED) { continue; }  // Skip processes already marked as killed
        printf("Killing process %d :::: %s\n", pmb->pids[i], pmb->commands[i]);
        kill(pmb->pids[i], signum);    // Send the specified signal to the process
        remove_from_process_map_block(pmb, pmb->pids[i]);  // Remove the process from the ProcessMapBlock
        count++;  // Increment the count of killed processes
    }
    if (count == 0) { printf("No processes to kill\n"); }
    else { printf("Killed %d processes\n", count); }  // Output the number of killed processes
}

// Function to free the memory allocated for the ProcessMapBlock
void destroy_process_map_block(ProcessMapBlock* pmb) {
    if (pmb == NULL) { return; } 
    free(pmb->pids);      
    free(pmb->commands);  
    free(pmb);            
}
