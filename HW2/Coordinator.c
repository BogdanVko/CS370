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
    
    for(int i = 0; i < 4; i++){
    int id;
    int p[2];
        
    pipe(p);
        
        id=fork();
        close(p[0]); 
        int shmID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666); //get mem
        printf("Coordinator: Created shared memory with ID: %d\n", shmID);

        int *shmPtr = (int *) shmat(shmID, NULL, 0);

        
        

         
        if (id < 0){
            fprintf(stderr, "Process Failed!");
            exit(1);
        }
        if(id == 0) {
            //Child
            write(p[1], &shmID, sizeof(int));
            close(p[1]);

            execlp("./checker", "Checker", argv[1], argv[i+2], p[0], NULL);
            
        }else{ //Parent

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
        //printf("Coordinator: exiting.\n");
    }
    
    printf("Coordinator: exiting.\n");
    return 0;
}