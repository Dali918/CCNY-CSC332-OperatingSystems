#include <stdio.h>
#include <unistd.h>
#include <errno.h>
int main(int argc, char *argv[])
{
    char *filepath = argv[1];
    int returnval;
    // Check file existence
    returnval = access(filepath, F_OK);
    if (returnval == 0)
        printf("\n %s exists\n", filepath);
    else
    {
        if (errno == ENOENT)
            printf("%s does not exist\n", filepath);
        else if (errno == EACCES)
            printf("%s is not accessible\n", filepath);
        return 0;
    }
    // Check read access
    returnval  = access(filepath, R_OK);
    if(returnval == 0){
        printf("\n %s has read acess\n", filepath);
    }
    else
    {
        if (errno == ENOENT)
            printf("%s does not exist\n", filepath);
        else if (errno == EACCES)
            printf("%s is not accessible\n", filepath);
        return 0;
    }

    returnval  = access(filepath, W_OK);
    //check write access 
    if(returnval == 0){
        printf("\n %s has write acess\n", filepath);
    }
    else
    {
        if (errno == ENOENT)
            printf("%s does not exist\n", filepath);
        else if (errno == EACCES)
            printf("%s is not accessible\n", filepath);
        return 0;
    }



    return 0;
}