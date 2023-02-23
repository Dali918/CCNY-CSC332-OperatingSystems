#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{

    char *source_filepath = argv[1];
    char *dest_filepath = argv[2];

    int exists = access(source_filepath, F_OK);
    int readaccess = access(source_filepath, R_OK);
    // error check file existence and access
    if (exists || readaccess || argc != 3)
    {
        if (argc != 3)
            printf("\ninsufficient arguments\n");
        else if (errno == ENOENT)
            printf("%s does not exist\n", source_filepath);
        else if (errno == EACCES)
            printf("%s is not accessible\n", source_filepath);
        return 0;
    }

    // open the source file in read only mode, -rw-r--r--
    int fd = open(source_filepath, O_RDONLY, 0644);
    // check if opened
    if (fd < 0)
    {
        perror("open");
        return 1;
    }
    // create buffer
    const int size = 1024;
    char buff[size];
    // read from file to buffer
    read(fd, buff, size);
    // print buffer contents
    printf("\n%s\n", buff);
    close(fd);
    // open destination filepath and wipe contents or create it
    int fd_next = open(dest_filepath, O_CREAT | O_WRONLY, 0644);
    // error check if open
    if (fd_next < 0)
    {
        perror("open");
        return 1;
    }
    // write the contents from buffer to destination
    ssize_t written = write(fd_next, buff, size);
    if (written < 0)
    {
        perror("write");
        close(fd_next);
        return 1;
    }
    // close the file and error check
    if (close(fd_next))
    {
        perror("close");
        return 1;
    }

    return 0;
}