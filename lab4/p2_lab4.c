#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// fork with child
// send signal to child with kill in parent
// receive signal
// raise sends a signal to a running process

void handler(int signum)
{
    printf("child has received signal %d\n", signum); //signal handler
    _exit(0);
}

int main()
{
    pid_t child_one; //child pid
    int status; //child status 

    if ((child_one = fork()) < 0) //error check forking
    {
        perror("Error Forking\n");
        exit(1);
    }
    else if (child_one == 0)    // child signal handling
    {
        // handle signal 1 and error check 
        if ((signal(SIGUSR1, handler)) == SIG_ERR)
        {
            perror("Error processign signal 1\n");
            _exit(1);
        }
        // handle signal 2 and error check 
        if ((signal(SIGUSR2, handler)) == SIG_ERR)
        {
            perror("Error processing signal 2\n");
            _exit(1);
        }

        exit(0);
    }
    else
    {
        sleep(1); //wait for child process to set up 

        // send and error check first signal 
        if ((kill(child_one, SIGUSR1)) == -1)
        {
            perror("Error sending user defined signal 1\n");
            return -1;
        }
        
        // send and error check second signal 
        if ((kill(child_one, SIGUSR2)) == -1)
        {
            perror("Error sending user defined signal 2\n");
            return -1;
        }

        // wait for the child process to terminate
        if (waitpid(child_one, &status, 0) < 1)
        {
            perror("Error with child status");
            exit(1);
        }
    }
    return 0;
}
