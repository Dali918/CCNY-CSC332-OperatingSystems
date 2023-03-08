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

    printf("starting parent process, pid: %d\n", getpid());

    if ((child_one = fork()) == -1)
    {
        // test child one fork
        perror("error child one fork");
        exit(EXIT_FAILURE);
    }
    else if (child_one == 0)
    {
        // only child one fork if pid == 0
        printf("\nchild process 1, pid: %d\n", getpid());

        // compile program
        if (system("gcc -o child q4_prcs_p1.c") == -1)
        {
            perror("system compile error");
            exit(EXIT_FAILURE);
        }
        // execute program with args using execv
        char *path = "./child";
        char *args[] = {"child", NULL};
        //error check execv
        if (execv(path, args) == -1)
        {
            perror("execv");
            exit(EXIT_FAILURE);
        }
        printf("\nterminating child process 1, pid: %d\n", getpid());
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
            printf("\nchild process 2 pid: %d\n", getpid());
            // compile programn 
            if (system("gcc -o child q4_prcs_p2.c") == -1)
            {
                perror("system compile error");
                exit(EXIT_FAILURE);
            }
            //execute program with args using execv
            char *path = "./child";
            char *args[] = {"child", "source.txt","destination1.txt", "destination2.txt",NULL};
            //error check execv
            if (execv(path, args) == -1)
            {
                perror("execv");
                exit(EXIT_FAILURE);
            }

            printf("\nterminating child process 2, pid: %d\n", getpid());
            return 0;
        }
        else
        {
            // wait for child two to finish
            waitpid(child_two, &status2, 0);
        }
    }

    printf("\nterminating parent process, pid: %d\n", getpid());

    return 0;
}