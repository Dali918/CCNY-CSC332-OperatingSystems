
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    pid_t child_one;
    char *source_filepath = argv[1];
    char *dest1_filepath = argv[2];
    int child_status;

    ssize_t chars_read = 0;
    ssize_t chars_written = 0;

    int pipefd[2];
    char c;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if ((child_one = fork()) == -1)
    {
        // test child one fork
        perror("error child one fork");
        return -1;
    }

    if (child_one == 0)
    {
        close(pipefd[0]); // close the read end of the pipe

        int fd_source; // file descriptor of the source file
        if ((fd_source = open(source_filepath, O_RDONLY, 0644)) < 0)
        {
            perror("source opening error\n");
            return -1;
        }

        while ((chars_read = read(fd_source, &c, 1)) == 1) // read from source file characater by character
        {
            // write to destination
            if ((chars_written = write(pipefd[1], &c, 1)) != 1) // write to the pipe
            {
                perror("writing error");
                return -1;
            }
        }

        close(pipefd[1]); // close the write end of the pipe when done
        close(fd_source); // close the source file descriptor
        return 0;
    }
    else
    {
        close(pipefd[1]); // close the unused write end
        waitpid(child_one, &child_status, 1);

        chars_written = 0;
        int fd_dest = open("destination1.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
        if (fd_dest == -1)
        {
            perror("Error creating destination1.txt");
            return -1;
        }

        char *header = "Parent is writing\n";

        if ((chars_written = write(fd_dest, header, strlen(header))) != strlen(header))
        {
            perror("Error writing header");
            return -1;
        }

        while ((chars_read = read(pipefd[0], &c, 1)) == 1) // read from pipe character by character
        {

            if ((chars_written = write(fd_dest, &c, 1)) != 1) // write character by character to destination
            {
                perror("writing error");
                return -1;
            }
        }

        close(fd_dest);
    }

    return 0;
}
