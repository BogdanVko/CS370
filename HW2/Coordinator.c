#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>
#include "Checker.h"




int main(int argc, char *argv[])
{

    
    

    int c[4];

    
    
    int frID[2]; ///pipe states
    int shID[4]; //IDs



    int a_counter = 2;
    while (a_counter < argc) // 4-2 =2
    {

        if (pipe(frID) == -1)
        {
            exit(1);
        }


        char str[30 * sizeof(char)];
        sprintf(str, "%d", frID[0]);


        shID[a_counter - 2] = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);





        

        if ((c[a_counter - 2] = fork()) == 0)
        {
            close(frID[1]);

           // printf("DERBUG: passing args: %d, %d" , atoi(argv[1], atoi()))
            execlp("./checker",  str, argv[1], argv[a_counter], NULL);
        }
        else
        {
            printf("Coordinator: forked process with ID %d.\n", c[a_counter - 2]);
            close(frID[0]);

            write(frID[1], &shID[a_counter - 2], sizeof(int)); ///write and don't forget to close!!
            close(frID[1]);
            printf("Coordinator: wrote shm ID %d to pipe (%d bytes)\n", shID[a_counter - 2], (int)sizeof(shID[a_counter - 2]));
        }
        a_counter++;
    }
    
    int actual_count = 0;
    while (actual_count < 4)
    {






        printf("Coordinator: waiting on child process ID %d...\n", c[actual_count]);
        waitpid(c[actual_count], NULL, 0);

        int *shared_ptr = shmat(shID[actual_count], NULL, 0);

        if (shared_ptr == (void *)-1)
           exit(1);
        

        int result_val;

        memcpy(&result_val, shared_ptr, 1); // checking

        int shmdt_return = shmdt(shared_ptr);

        if (shmdt_return == -1)
            exit(1);

        if (shmctl(shID[actual_count], IPC_RMID, NULL) == -1)
            exit(1);


        int devisor = atoi(argv[1]);
        int arg_dev = atoi(argv[actual_count + 2]);
        if (result_val == 0)
        {
            printf("Coordinator: result %d read from shared memory: %d is not divisible by %d.\n", result_val, arg_dev, devisor);
        }

        
        else
        {
            printf("Coordinator: result %d read from shared memory: %d is divisible by %d.\n", result_val, arg_dev, devisor);
        }
        actual_count++;
    }



    printf("Coordinator: exiting.\n");

    return 0;
}