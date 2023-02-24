#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

const int buff_size = 2048;

int main(int argc, char *argv[])
{
    char *filepath = argv[1];
    int exists, readaccess, fd;
    exists = access(filepath, F_OK);
    readaccess = access(filepath, R_OK);
    // error check fargument count, file existence, and access
    if (exists || readaccess || argc!=2)
    {
        if(argc!=2)
            printf("not enough or too many argments\n");
        else if (errno == ENOENT)
            printf("%s does not exist\n", filepath);
        else if (errno == EACCES)
            printf("%s is not accessible\n", filepath);
        return 0;
    }
    //open the file and errorcheck open operation
    fd = open(filepath, O_RDWR);
    if (fd < 0)
    {
        perror("error open file");
        return 1;
    }
    // number of bytes read
    ssize_t char_read;
    //create buffer
    char buff[buff_size];
    // read and error check reading operation
    char_read = read(fd, buff, buff_size);
    if (char_read < 0)
    {
        perror("error reading file");
        return 1;
    }
    // print to terminal
    printf("%s",buff);
    //close file descriptor
    close(fd);
    return 0;
}