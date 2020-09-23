#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/resource.h>
#include <sys/mman.h>



int main(int argc, char **argv)
{
    if (argc != 6){
        printf("Enter only 5 arguments!\n");
        return 0;

    }
    int id;
    for(int i = 0; i < 4; i++){

        id=fork();
        if (id < 0){
            fprintf(stderr, "Process Failed!");
            return 1;
        }
        if(id == 0) {
            //Child
            
            execlp("./checker", "Checker", argv[1], argv[i+2], NULL);
            
        }else{
            printf("Coordinator: forked process with ID %u.\n", id);
            printf("Coordinator: wainting for process [%u].\n", id);
            int updt;

            waitpid(id, &updt, 0);
            if(WIFEXITED(updt)){
                int status = WEXITSTATUS(updt);
                printf("Coordinator: child process %u retuned: %d.\n", id, status);
                continue;
            }

        }
        printf("Coordinator: exiting.\n");
    }
    
    printf("Coordinator: exiting.\n");
    return 0;
}