# fsh (First Shell) Project

## Description

The **fsh (First Shell)** project is a simple shell implemented in C that simulates basic Unix shell functionalities. The main goal of this project is to explore process manipulation, signal handling, and command execution in a controlled manner.

### Features

1. **Prompt and Command Input**
   - The shell prompt is `fsh>`.
   - The shell allows executing multiple commands on the same line, separated by the `#` symbol.

2. **Foreground and Background Processes**
   - The first command on the line is executed in the foreground.
   - Subsequent commands are executed in the background.
   - Each background process also spawns a secondary process that executes the same command.

3. **Signal Handling**
   - **SIGINT (Ctrl-C)**: If the shell has live descendants, it prompts the user to confirm if they want to terminate. If there are no live descendants, the shell exits immediately.
   - **SIGTSTP (Ctrl-Z)**: Suspends all child processes of the shell, but not the shell itself.
   - During SIGINT handling, all other signals must be blocked.
   - All child processes of the shell must ignore SIGINT.

4. **Internal Shell Commands**
   - `waitall`: Cleans up all zombie child processes.
   - `die`: Terminates the shell and all its descendants.

5. **Command Language**
   - **Internal Commands**: Commands like `waitall` and `die` are executed by the shell itself.
   - **Special Operators**: Only the `#` symbol is used to separate commands.
   - **Executable Programs**: Commands that execute external programs and may have up to two arguments.

## Compilation

To compile the project, use the following command:

```sh
gcc -o fsh fsh.c
```

Ensure that the source code file `fsh.c` is in the current directory.

## Execution

To run the shell, use the following command:

```sh
./fsh
```

## Usage

1. Execute Simple Commands
    - Example: `fsh> ls -l`

2. Execute Multiple Commands
    - Example: `fsh> command1 # command2 # command3`

3. Internal Commands
    - `waitall`: Waits for all zombie child processes to be cleaned up.
    - `die`: Terminates the shell and all child processes.

4. Signal Handling 
    - Press `Ctrl-C` to send SIGINT.
    - Press `Ctrl-Z` to send SIGTSTP