#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

const int buff_size = 1024;

int main(int argc, char *argv[])
{

    char *source_filepath = argv[1];
    char *dest_filepath = argv[2];
    // create buffer
    char buff[buff_size];
    // existence and access checks
    int exists = access(source_filepath, F_OK);
    int readaccess = access(source_filepath, R_OK);
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
    int fd_source = open(source_filepath, O_RDONLY, 0644);
    // open destination filepath in write only mode and wipe contents or create it, -rw-r--r--
    int fd_dest = open(dest_filepath, O_WRONLY| O_CREAT | O_TRUNC, 0644);
    // error check open
    if (fd_source < 0)
    {
        perror("open source fail");
        return 1;
    }
    if (fd_dest < 0)
    {
        perror("open dest fail");
        return 1;
    }
    // number of bytes read and written
    ssize_t char_read;
    ssize_t char_write;
    // read from file to buffer and error check
    char_read = read(fd_source, buff, buff_size);
    if (char_read < 0)
    {
        perror("read source file fail");
        return 1;
    }
    // write from buffer to dest and error check
    char_write = write(fd_dest, buff, sizeof(buff));
    if (char_read < 0 || char_read != char_write)
    {
        perror("write dest file fail");
        return 1;
    }
    // close file descriptors
    close(fd_source);
    close(fd_dest);

    return 0;
}