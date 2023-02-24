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
    //argument testing
    if (argc != 2)
    {
        printf("File parameter is missing\n");
        return 1;
    }
    errno = 0;
    char *filepath = argv[1];
    //create and error check
    fd = open(filepath, O_CREAT | O_RDWR);
    if (fd < 0)
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
    //  Test for existence 
    int returnval = access(filepath, F_OK);
    if (returnval == 0)
        printf("\n %s exists\n", filepath);
    else{
        printf("\n %s does not exist and was not created\n", filepath);
    }
    // close file descriptor
    close(fd);
    return 0;
}