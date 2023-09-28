#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>

void help() {
        printf("This program is designed to have a parent process fork off into child processes.\n");
	printf("The child processes don't do anything special: they simply output their parent's\n");
	printf("process id, their own process id, and the number of times that the child has looped.\n\n");
        printf("The executable takes three flags: [-n proc], [-s simul], and [-t iter].\n");
        printf("The value of proc determines the total number of child processes to be produced.\n");
	printf("The value of simul determines the number of children that can run simultaneously.\n");
	printf("The value of iter determines the number of times each child process will loop.\n");
	printf("\nMADE BY JACOB (JT) FOX\nSeptember 14th, 2023\n");
	exit(1);
}

void incrementClock(int *shm_ptr) {
	shm_ptr[1] += 10000;
	if(shm_ptr[1] >= 1000000000) {
		shm_ptr[1] = 0;
		shm_ptr[0] += 1;
	}
}


/* TODO
 * Revise the help and README
 * Create shared memory using ftok and shmget
 * Iterate the 'system clock' using nested for loops i guess?
 * 
 */

int main(int argc, char** argv) {
	int option;
	int proc;
	int simul;
	int timelimit;

	//allocate shared memory
	const int sh_key = ftok("./oss.c", 0);
	const int shm_id = shmget(sh_key, sizeof(int) * 2, IPC_CREAT | 0666);
	if(shm_id <= 0) {
		printf("Shared memory allocation failed\n");
		exit(1);
	}
	//printf("id: %d\n", shm_id);

	//attach to shared memory
	int *shm_ptr;
	shm_ptr = shmat(shm_id, 0 ,0);
	if(shm_ptr <= 0) {
		printf("Attaching to shared memory failed\n");
		exit(1);
	}

	//set clock to zero
	shm_ptr[0] = 0;
	shm_ptr[1] = 0;

	while ((option = getopt(argc, argv, "hn:s:t:")) != -1) {
  		switch(option) {
   			case 'h':
    				help();
    				break;
   			case 'n':
    				proc = atoi(optarg);
    				break;
   			case 's':
				simul = atoi(optarg);
				break;
			case 't':
				timelimit = atoi(optarg);
				break;
		}
	}

	struct PCB {
		int occupied;
		pid_t pid;
		int startTimeSec;
		int startTimeNano;
	};

	struct PCB processTable[proc];

	int totalChildren;
	int runningChildren;
	int finalChild;
	totalChildren = 0;
	runningChildren = 3; //this might be problematic

	//test to see if the latest worker to be initiated has completed its operation?

	/*while(totalChildren < proc) { 
  		pid_t childPid = fork();
       		finalChild = childPid;
       		totalChildren++;
       		runningChildren++;
                                
      		if(childPid == 0) {
       			execlp("./worker", iter, NULL);
       			exit(1);
       		}
       		else{
       			if(runningChildre
       				wait(0);
       				runningChildren--;
       		}
       	}*/

	char test = 'c';
	char *param = &test;
	do { //Children are running if a PCB is occupied
		incrementClock(shm_ptr);

		printf("oss clock: %d : %d\n", shm_ptr[0], shm_ptr[1]);

		/*if(sixtySecondsHasPassed)
			terminateProgram();
		
		if(halfSecondHasPassed)
			outputTable();*/

	//int pid = waitpid(-1, &status, WNOHANG); //Will return 0 if no processes have terminated
		//if(pid) {
		//	endPCB(); //Show in the process table that this child is not being used, ie occupied = false
		//	runningChildren--;
		//	if(runningChildren < simul) {
				pid_t childPid = fork(); //Launches child
				if(childPid == 0) {
					execlp("./worker", param, NULL);
					exit(1);
				}
				else {
					printf("childPid: %d\n", childPid);
				}
		//		startPCB(); //Add pid to PCB and set to occupied, set start time
		//		runningChildren++;
		//	}
		//}
		runningChildren--;
	} while(runningChildren);	

	pid_t wpid;
	int status = 0;
	while((wpid = wait(&status)) > 0);
	//detach from and delete memory
	shmdt(shm_ptr);
	shmctl(shm_id, IPC_RMID, NULL);
	return EXIT_SUCCESS;
}

