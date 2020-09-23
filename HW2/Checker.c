#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>

#include "Checker.h"

int main(int argc, char **argv)
{
    int id;
    id =  getpid();
    printf("Checker process [%u]: Starting.", id); 
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    
    if (y % x == 0){
        printf("Checker process [%u]: %d *IS* divisible by %d.", id, y, x);
        printf("Checker process [%u]: Returning %d.", id, 1);
        return 1;
    }else{
        printf("Checker process [%u]: %d *IS NOT* divisible by %d.", id, y, x);
        printf("Checker process [%u]: Returning %d.", id, 0);
        return 0; 
    }
    

}