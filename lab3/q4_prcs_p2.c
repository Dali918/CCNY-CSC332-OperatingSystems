#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    // source and destination file-paths
    char *source_filepath = argv[1];
    char *dest1_filepath = argv[2];
    char *dest2_filepath = argv[3];

    if (argc != 4)
    {
        printf("not enough or too many arguments\n");
        return -1;
    }

    int fd_source, fd_dest1, fd_dest2, fd_current_dest;
    // open the source file in read only mode
    if ((fd_source = open(source_filepath, O_RDONLY, 0644)) < 0)
    {
        perror("source error\n");
        return -1;
    }
    // open dest 1 file in write only mode
    if ((fd_dest1 = open(dest1_filepath, O_WRONLY, 0666)) < 0)
    {
        perror("dest1 error\n");
        return -1;
    }
    // open dest 2 in write only mode
    if ((fd_dest2 = open(dest2_filepath, O_WRONLY, 0666)) < 0)
    {
        perror("dest2 error\n");
        return -1;
    }

    // storage for number bytes read and written
    ssize_t chars_written = 0;
    ssize_t chars_read = 0;
    char c;        // char buffer
    int count = 0; // counter for destination switching
    // read 1 byte
    while ((chars_read = read(fd_source, &c, 1)) == 1)
    {
        // for destination 1
        if (count < 100)
        {
            fd_current_dest = fd_dest1;

            if (c == '1')
            {
                c = 'L';
            }
        }
        else
        // for destination 2
        {

            fd_current_dest = fd_dest2;
            if (c == '3')
            {
                c = 'E';
            }
        }
        // write to destination
        if ((chars_written = write(fd_current_dest, &c, 1)) != 1)
        {
            perror("writing error");
            return -1;
        }
        // reset counter
        count++;
        if (count == 150)
        {
            count = 0;
        }
    }
    // check source reading error
    if (chars_read < 0)
    {
        perror("source reading error");
        return -1;
    }
    
    //close file descriptors
    close(fd_dest1);
    close(fd_dest2);
    close(fd_source);

    return 0;
}