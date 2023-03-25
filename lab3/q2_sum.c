
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int calc_sum(int start, int step, int end);

int main(int argc, char *argv[])
{
    pid_t child_one;
    pid_t child_two;

    int status1, status2;
    int start, step, end;
    int s1, s2, s3;
    //check argument count
    if(argc!=2){
        printf("invalid argument count\n");
        return 1;
    }
    //getting end sum 
    end = atoi(argv[1]);
    step = 2;
    
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
        start = 1;
        return calc_sum(start, step, end);

        // calc_sum(start, step, end, &s1);
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
            start = 2;
            return calc_sum(start, step, end);
        }
        else
        {
            // terminate child processes
            waitpid(child_one, &status1, 0);
            waitpid(child_two, &status2, 0);
            //get return values from child statuses
            s1 = WEXITSTATUS(status1);
            s2 = WEXITSTATUS(status2);
            //calculate sum 
            s3 = s1 + s2;
            printf("s1 is: %d\n", s1);
            printf("s2 is: %d\n", s2);
            printf("s3 is: %d\n", s3);
            printf("terminating parent process, pid: %d\n", getpid());
        }
    }

    return 0;
}

int calc_sum(int start, int step, int end)
{
    int sum = 0;
    for (int i = start; i <= end; i += step)
    {
        sum += i;
    }

    return sum;
}