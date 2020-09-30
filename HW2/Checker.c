
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	





    int prog_ID = atoi(argv[0]);
    int devisor= atoi(argv[1]);
	int devider= atoi(argv[2]);
	



	printf("Checker process [%d]: starting.\n", getpid());
    int shmID;
	read(prog_ID, &shmID, sizeof(int));
	close(prog_ID);

	printf("Checker process [%d]: read %d bytes containing shm ID %d\n", getpid(), (int) sizeof(shmID), shmID);

	int *shared_ptr = shmat(shmID, NULL, 0);
        ///Check for errors
	
	if ( devider % devisor == 0 ){
		printf("Checker process [%d]: %d *IS* divisible by %d.\n", getpid(), devider, devisor);
		memset(shared_ptr, 1, sizeof(int));
		printf("Checker process [%d]: wrote result (1) to shared memory.\n", getpid());
	}
	else {
		printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", getpid(), devider, devisor);
		memset(shared_ptr, 0, sizeof(int));
		printf("Checker process [%d]: wrote result (0) to shared memory.\n", getpid());
	}

	int sharereturn = shmdt(shared_ptr);

	if (sharereturn == -1)
		exit(1);

	return 0;
}