#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_NUM_ARGS 9
#define MAX_COMMAND_LENGTH 180

void executeCommand(char *args[])
{
    pid_t child_pid = fork();

    if (child_pid < 0)
    { // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (child_pid == 0)
    { // Child process
        if (execvp(args[0], args) == -1)
        {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
    else
    { // Parent process
        int status;
        waitpid(child_pid, &status, 0); // Wait for child process to finish
    }
}

int tokenizeCommand(char *command, char *args[])
{
    int argCount = 0;
    char *token = strtok(command, " "); // Tokenize the command

    while (token != NULL && argCount < MAX_NUM_ARGS)
    {                              // Iterate through tokens
        args[argCount++] = token;  // Store token in args array
        token = strtok(NULL, " "); // Get next token
    }

    args[argCount] = NULL; // Last entry in args is set to NULL
    return argCount;       // Return the argument count
}

int main()
{
    char command[MAX_COMMAND_LENGTH]; // Store user command
    char *args[MAX_NUM_ARGS + 1];     // +1 for NULL termination
    char *pipe_operator;
    char *command_part2;

    while (1)
    {
        printf("Enter command: ");

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        command[strcspn(command, "\n")] = '\0'; // Remove newline character

        if (strcmp(command, "exit") == 0)
        {
            break; // Exit the loop if the command is "exit"
        }

        pipe_operator = strchr(command, '|'); // Check for pipe operator

        if (pipe_operator != NULL)
        {                          // If pipe operator exists in the command
            *pipe_operator = '\0'; // Split the command at the pipe operator
            command_part2 = pipe_operator + 1;

            int argCount = tokenizeCommand(command, args); // Tokenize first command

            int pipefd[2];
            if (pipe(pipefd) < 0)
            { // Create a pipe
                perror("pipe");
                exit(EXIT_FAILURE);
            }

            executeCommand(args); // Execute the first command

            argCount = tokenizeCommand(command_part2, args); // Tokenize second command

            dup2(pipefd[0], STDIN_FILENO); // Redirect stdin of the second command to the pipe
            close(pipefd[1]);              // Close the write end of the pipe

            executeCommand(args); // Execute the second command

            close(pipefd[0]); // Close the read end of the pipe
            wait(NULL);       // Wait for the second command to finish
        }
        else
        {                                                  // If no pipe operator exists in the command
            int argCount = tokenizeCommand(command, args); // Tokenize the command
            executeCommand(args);                          // Execute the command
        }
    }

    return 0;
}
