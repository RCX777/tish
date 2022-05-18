// Handles the execution of new processes

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

#include "colors.h"
#include "exec.h"


#define  READ_FD  0
#define  WRITE_FD 1


// Function that executes the following system command
void exec_args(char** args)
{
    pid_t pid = fork();

    switch (pid) {
    case -1:
        fprintf(stderr, RED"%s: Could not fork child!\n"RES, args[0]);
        return;
    case  0:
        // Child is executing
        if (execvp(args[0], args) < 0) {
            fprintf(stderr, RED"%s: Command does not exist!\n"RES, args[0]);
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    default:
        // Waiting for child process to end
        wait(NULL);
    }
}

// Function that executes both commands at each of the pipe ends
void exec_args_piped(char** args, char** args_piped)
{
    int pipefd[2];

    pid_t pid1;
    pid_t pid2;

    if (pipe(pipefd) < 0) {
        fprintf(stderr, RED"%s: Could not create pipe!\n"RES, args[0]);
        return;
    }

    switch (pid1 = fork()) {
    case -1:
        fprintf(stderr, RED"%s: Could not fork child!\n"RES, args[0]);
        return;
    
    case  0:
        // First child writes data to the write end of the pipe
        close(pipefd[READ_FD]);
        dup2(pipefd[WRITE_FD], STDOUT_FILENO);
        close(pipefd[WRITE_FD]);

        execvp(args[0], args); // Executing first command

        // Reached only in the case of an error
        fprintf(stderr, RED"%s: Command does not exist!\n"RES, args[0]);
        exit(EXIT_FAILURE);

    default:
        // Parent is executing and waiting for the first child
        int status;

        waitpid(pid1, &status, 0);

        // Prevent execution if first child has exited with an error code
        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
            return;

        switch (pid2 = fork()) {
        case -1:
            fprintf(stderr, RED"%s: Could not fork child!\n"RES,
                    args_piped[0]);
            return;

        case 0:
            // Second child is reading from the read end of the pipe
            close(pipefd[WRITE_FD]);
            dup2(pipefd[READ_FD], STDIN_FILENO);
            close(pipefd[READ_FD]);

            execvp(args_piped[0], args_piped); // Executing second command

            // Reached only in the case of an error
            fprintf(stderr, RED"%s: Command does not exist!\n"RES,
                    args_piped[0]);
            exit(EXIT_FAILURE);

        default:
            // Parent is executing and waiting for the second child
            close(pipefd[READ_FD]);
            close(pipefd[WRITE_FD]);

            waitpid(pid2, NULL, 0);
        }
    }
}