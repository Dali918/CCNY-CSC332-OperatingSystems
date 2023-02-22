#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char *filepath = argv[1];
    int exists, readaccess;
    exists = access(filepath, F_OK);
    readaccess = access(filepath, R_OK);
    //error check file existence and access
    if (exists != 0 || readaccess != 0)
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

   
    

    return 0;
}