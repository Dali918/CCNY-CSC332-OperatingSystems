#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    char *filepath = argv[1];
    int exists, readaccess, fd;
    exists = access(filepath, F_OK);
    readaccess = access(filepath, R_OK);
    // error check file existence and access
    if (exists || readaccess)
    {
        if (errno == ENOENT)
            printf("%s does not exist\n", filepath);
        else if (errno == EACCES)
            printf("%s is not accessible\n", filepath);
        return 0;
    }

    printf("\nThe file is good\n");

    /*
    you are to use the following system calls:
    open(),
    read(),
    write(),
    close()
    */

    fd = open(filepath, O_RDWR);

    if (fd == -1)
    {
        perror("error");
        return 1;
    }
    else
    {
        printf("\n Open() successful\n");
        /* open() succeeded, now one can do read operations on the file
        since we opened it in read-only mode. Also once done with processing,
        file needs to be close */
    }

    const int size = 200;
    char buff[size];
    read(fd, buff, size);
    printf("\n%s\n", buff);

    close(fd);

    return 0;
}