#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main()
{
    int shmid = shmget(12345, 5, IPC_CREAT | 0666); // Declare shared memory
    if (shmid == -1)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    char *shared_mem = (char *)shmat(shmid, NULL, 0); // Declare shared memory
    if (shared_mem == (char *)-1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Initialize shared memory with 'A's
    for (int i = 0; i < 5; i++)
    {
        shared_mem[i] = 'A';
    }

    // Fork Process A
    pid_t A = fork();
    if (A == -1)
    {
        perror("Fork");
        exit(EXIT_FAILURE);
    }
    else if (A == 0)
    {
        while (shared_mem[0] != 'B')
        {
        } // Wait for Process B to update
        printf("Process A: %c%c%c%c%c\n", shared_mem[0], shared_mem[1], shared_mem[2], shared_mem[3], shared_mem[4]);
        exit(EXIT_SUCCESS);
    }

    // Fork Process B
    pid_t B = fork();
    if (B == -1)
    {
        perror("Fork");
        exit(EXIT_FAILURE);
    }
    else if (B == 0)
    {
        shared_mem[0] = 'B';
        while (shared_mem[0] != 'C')
        {
        } // Wait for Process C to update
        printf("Process B: %c%c%c%c%c\n", shared_mem[0], shared_mem[1], shared_mem[2], shared_mem[3], shared_mem[4]);
        exit(EXIT_SUCCESS);
    }

    // Fork Process C
    pid_t C = fork();
    if (C == -1)
    {
        perror("Fork");
        exit(EXIT_FAILURE);
    }
    else if (C == 0)
    {
        shared_mem[0] = 'C';
        printf("Process C: %c%c%c%c%c\n", shared_mem[0], shared_mem[1], shared_mem[2], shared_mem[3], shared_mem[4]);
        shmdt(shared_mem); // Detach shared memory
        exit(EXIT_SUCCESS);
    }

    // Wait for child processes
    waitpid(A, NULL, 0);
    waitpid(B, NULL, 0);
    waitpid(C, NULL, 0);

    shmdt(shared_mem);             // Detach shared memory
    shmctl(shmid, IPC_RMID, NULL); // Delete shared memory

    return 0;
}
