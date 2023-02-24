#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

const int buff_size = 100;

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

    // open the source file in read only mode, -rw-rw-rw- permissions
    int fd_source = open(source_filepath, O_RDONLY, 0644);
    int fd_dest = open(dest_filepath, O_CREAT | O_WRONLY, 0666);

    if (!fd_source || !fd_dest)
    {
        perror("error");
        return 1;
    }
    // store number bytes read and written
    ssize_t chars_written;
    ssize_t chars_read;
    //create buffer with 100 characters
    char buff[buff_size];
    //loop as long as number bytes read is greater than 0
    while ((chars_read = read(fd_source, buff, buff_size)) > 0)
    {
        //go through the buffer and change chars
        for (int i = 0; i < buff_size; i++)
        {
            if (buff[i] == '1')
            {
                buff[i] == 'L';
            }
        }
        // write buffer chars to file
        chars_written = write(fd_dest, buff, buff_size);
        //write XYZ chars to file
        chars_written = write(fd_dest, "XYZ", 3);
        // error check writing to file
        if (chars_written  < 0)
        {
            perror("write");
            return 1;
        }
    }
    //error check chars read if failed above
    if (chars_read < 0)
    {
        perror("write");
        return 1;
    }
    //close file descriptors
    close(fd_source);
    close(fd_dest);

    return 0;
}