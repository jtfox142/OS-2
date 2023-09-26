#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char** argv) {
	int iterations;
	iterations = atoi(argv[0]);
	pid_t ppid = getppid();
	pid_t pid = getpid();
  	int i;
  	for (i = 1; i <= iterations; i++) {
		printf("WORKER PID:%d PPID:%d Iteration:%d before sleeping\n", pid, ppid, i);
 		sleep(1);
		printf("WORKER PID:%d PPID:%d Iteration:%d after sleeping\n", pid, ppid, i);
	}
	return EXIT_SUCCESS;
}
