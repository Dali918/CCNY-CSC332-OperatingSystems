#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
typedef void (*sighandler_t)(int);

void signal_handler(int signal)
{
    printf("Child process received signal %d\n", signal);
}

int main()
{

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        sighandler_t sig1, sig2;
        // set up signal 1
        sig1 = signal(SIGUSR1, signal_handler); // assign
        if (sig1 == SIG_ERR)
        {
            perror("Failure setting up signal 1");
            exit(EXIT_FAILURE);
        }
        //set up signal 2
        sig2 = signal(SIGUSR2, signal_handler); // SIGNAL FOR CHILD
        if (sig2 == SIG_ERR)
        {
            perror("Failure setting up signal 2");
            exit(EXIT_FAILURE);
        }
        pause(); // wait 
    }
    else
    {
        sleep(1); // wait for child process to set up signals
        kill(pid, SIGUSR1);                      // send the signals 
        kill(pid, SIGUSR2);                      // kilss the signal
    }

    return 0;
}
