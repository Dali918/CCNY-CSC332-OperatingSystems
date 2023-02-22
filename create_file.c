#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
int main(int argc, char *argv[])
{
    int fd;
    if (argc != 2)
    {
        printf("File parameter is missing\n");
        return 1;
    }
    errno = 0;
    fd = open(argv[1], O_CREAT | O_RDWR,
              S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (fd == -1)
    {
        printf("\n open () failed with error [%s]\n", strerror(errno));
        return 1;
    }
    else
    {
        printf("\n Open() successful\n");
        /* open() succeeded, now one can do read operations on the file
        since we opened it in read-only mode. Also once done with processing,
        file needs to be close */
    }
    close(fd);
    return 0;
}