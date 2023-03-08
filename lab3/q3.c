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
        printf("I am child one, my pid is: %d\n", getpid());
    }
    else
    {
        // parent process
        if ((child_two = fork()) == -1)
        {
            // check child process two
            perror("error child two fork");
            return -1;
        }
        else if (child_two == 0)
        {
            // child process two success
            printf("I am child two, my pid is: %d\n", getpid());
        }
        else
        {
            // terminate processes
            waitpid(child_one, &status1, 0);
            waitpid(child_two, &status2, 0);
            printf("terminating parent process, pid: %d\n", getpid());
        }
    }

    return 0;
}