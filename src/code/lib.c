#include "../libs/lib.h"
#include <string.h>     
#include <stdlib.h>     
#include <stdio.h>      
#include <unistd.h>     

// Function to read commands from standard input and store them in the 'commands' array
void read_commands_stdin(char** commands) {
    char *line = NULL;         // Pointer to store the input line
    size_t len = 0;           // Variable to hold the size of the buffer
    ssize_t read;             // Variable to store the result of getline

    read = getline(&line, &len, stdin); // Read a line from standard input
    if (read == -1) { return; }

    int i = 0;
    // Split the input line by '#' character and process each token
    for (char *c = strtok(line, "#"); c; c = strtok(NULL, "#")) {
        // Allocate memory for the command and copy the token into it
        commands[i] = malloc(strlen(c) + 1);
        if (c[0] == ' ')  // Remove leading spaces
            c++;
        if (c[strlen(c) - 1] == '\n')  // Remove trailing newline
            c[strlen(c) - 1] = '\0';
        commands[i++] = c;  // Store the command and move to the next index
    }
}

// Function to parse a command string into an argument array for execvp
char **get_args_execvp(char *command) {
    char **args = malloc((MAX_ARGS + 1) * sizeof(char *));  // Allocate memory for arguments array

    int i = 0;
    // Split the command string by spaces and process each token
    for (char *c = strtok(command, " "); c; c = strtok(NULL, " ")) {
        // Allocate memory for the argument and copy the token into it
        args[i] = malloc(strlen(c) + 1);
        if (c[0] == ' ')  // Remove leading spaces
            c++;
        if (c[strlen(c) - 1] == '\n')  // Remove trailing newline
            c[strlen(c) - 1] = '\0';
        args[i++] = c;  // Store the argument and move to the next index
    }
    args[i] = NULL;  // Null-terminate the arguments array

    return args;  // Return the arguments array
}

// Function to get or set the stored commands based on the mode
char** get_set_commands(char** commands, char* mode) {
    static char** stored_commands = NULL;  // Static variable to store commands
    
    if (strcmp(mode, "set") == 0) {   // If mode is "set", update the stored commands
        stored_commands = commands;
    }
    
    if (strcmp(mode, "get") == 0) {   // If mode is "get", return the stored commands
        return stored_commands;
    }

    return NULL;  // Return NULL if the mode is not recognized
}
