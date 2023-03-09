#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
int main(int argc, char *argv[])
{

    int fd1, fd2;
    // create file destination 1
    fd1 = open("destination1.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd1 == -1)
    {
        perror("Error creating destination1.txt");
        return -1;
    }
    // create file destination 2
    fd2 = open("destination2.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd1 == -1)
    {
        perror("Error creating destination2.txt");
        return -1;
    }
    // close file descriptors
    close(fd1);
    close(fd2);
    return 0;
}