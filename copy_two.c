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

    // open the source file in read only mode, -rw-rw-rw- permissions
    int fd = open(source_filepath, O_RDONLY, 0644);
    int fd_write = open(dest_filepath, O_CREAT | O_WRONLY, 0666);

    if (!fd || !fd_write)
    {
        perror("error");
        return 1;
    }

    char ch;
    ssize_t written;
    ssize_t file_read;
    int count = 0;
    while (read(fd, &ch, 1) == 1)
    {
        count++;
        // write the contents from buffer to destination
        if (count == 100)
        {
            char word[3] = {'W', 'Y', 'Z'};
            written = write(fd_write, &word, 3);
            count = 0;
        }
        else
        {
            written = write(fd_write, &ch, 1);
        }

        // error check
        if (written < 0)
        {
            perror("write");
            close(fd_write);
            return 1;
        }
    }

    return 0;
}