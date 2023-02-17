#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char*argv[]){
    int x = 10;
    int y =20;

    int z = x+y;
    int m = y-x;

    printf("%d\n",z);
    printf("%d\n",m);
    int q = atoi(argv[1]) + atoi(argv[2]);
    printf("From terminal: %d + %d = %d\n",atoi(argv[1]),atoi(argv[2]),q);
    return 0;

}