#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMANDS 5
#define MAX_ARGS 2

/// @brief Reads commands from standard input and stores them in the provided array.
/// 
/// This function reads a line from standard input, splits it by the '#' character,
/// and stores each resulting command in the `commands` array. Leading and trailing
/// spaces and newlines are removed from each command.
/// 
/// @param commands Array of pointers to store the read commands. The caller should
///                 allocate enough space for `MAX_COMMANDS` pointers.
void read_commands_stdin(char** commands);

/// @brief Parses a command string into an array of arguments suitable for `execvp`.
/// 
/// This function splits the given command string by spaces and allocates memory for
/// each argument. It also removes leading and trailing spaces and newlines from
/// each argument.
/// 
/// @param command The command string to be parsed.
/// @return A dynamically allocated array of strings representing the arguments.
///         The array is null-terminated and should be freed by the caller.
char **get_args_execvp(char *command);

/// @brief Sets or gets stored commands based on the provided mode.
/// 
/// This function can be used to set or get the stored commands. When in "set" mode,
/// it updates the stored commands. When in "get" mode, it returns the currently
/// stored commands.
/// 
/// @param commands Array of command strings to be stored, or NULL if mode is "get".
/// @param mode The mode of operation: "set" to store commands, "get" to retrieve them.
/// @return The currently stored commands if mode is "get", or NULL if mode is not recognized.
char** get_set_commands(char** commands, char* mode);
