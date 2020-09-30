#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>

#include "Checker.h"

int main(int argc, char **argv)
{  
    int n;
    read(argv[1], &n, sizeof(int));
    int* ptr =(int *) shmat(n, NULL, 0);
    

    if (argc != 3){
        printf("Enter 3 arguments!\n");
        return 0;

    }
    
    int id;
    id =  getpid();
    printf("Checker process [%u]: read 4 bytes containing shm ID %d\n", id, atoi(argv[1])); 
    int x = atoi(argv[2]);
    int y = atoi(argv[3]);
    
    if (y % x == 0){
        printf("Checker process [%u]: %d *IS* divisible by %d.\n", id, y, x);
        printf("Checker process [%u]: Returning %d.\n", id, 1);
        exit(1);
    }else{
        printf("Checker process [%u]: %d *IS NOT* divisible by %d.\n", id, y, x);
        printf("Checker process [%u]: Returning %d.\n", id, 0);
        exit(0);
    }
    

}