#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t child_one;
    pid_t child_two;

    int status1, status2;

    printf("starting parent process: %d\n", getpid());

    if ((child_one = fork()) == -1)
    {
        // test child one fork
        perror("error child one fork");
        return -1;
    }
    else if (child_one == 0)
    {
        // only child one fork if pid == 0
        printf("\nI am child one, my pid is: %d\n", getpid());
        // path for date exec
        char *path = "/bin/date";
        if (execl(path, path, NULL) == -1)
        {
            printf("failed to execute in child process 1\n");
            return -1;
        }

        return 0;
    }
    else
    {
        // wait for child to finish
        waitpid(child_one, &status1, 0);
        // parent process
        if ((child_two = fork()) == -1)
        {
            // check child process two
            perror("error child two fork");
            return -1;
        }
        else if (child_two == 0)
        {
            // announce child two process
            printf("\nI am child two, my pid is: %d\n", getpid());
            // child execvp
            char *command = "ls";
            // child two execvp call to list all files including hidden
            char *args[] = {command, "-la", NULL};
            if (execvp(command, args) == -1)
            {
                printf("failed to execute in child process 2\n");
                return -1;
            }

            return 0;
        }
        else
        {
            // wait for child two to finish
            waitpid(child_two, &status2, 0);
            printf("\nterminating parent process, pid: %d\n", getpid());
        }
    }

    return 0;
}