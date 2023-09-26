#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

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

int main(int argc, char** argv) {
	int option;
	int proc;
	int simul;
	char *iter;

	while ((option = getopt(argc, argv, "hn:s:t:")) != -1) {
  		switch(option) {
   			case 'h':
    				help();
    				break;
   			case 'n':
    				proc = atoi(optarg); //Made these two params into integers to make comparisons simpler
    				break;
   			case 's':
				simul = atoi(optarg);
				break;
			case 't':
				iter = optarg; //Kept this a char * so I could pass it easier
				break;
		}
	}
	int totalChildren;
	int runningChildren;
	int finalChild;
	totalChildren = 0;
	runningChildren = 0;

    	while(totalChildren < proc) { 
		pid_t childPid = fork();
		finalChild = childPid; //Gets reassigned every time the loop runs. A sloppy but effective way to get the final child's pid
		totalChildren++;
		runningChildren++;

		if(childPid == 0) {
			execlp("./worker", iter, NULL);
			exit(1);
		}
		else{
			if(runningChildren >= simul) {
				wait(0);
				runningChildren--; //R.I.P.
			}
		}
	}
	pid_t waitForAllStop = waitpid(finalChild, NULL, 0); //ensures parent doesn't end before final child
  	return EXIT_SUCCESS;
}

