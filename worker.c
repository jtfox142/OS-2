#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main(int argc, char** argv) {
	int iterations;
	//iterations = atoi(argv[0]);
	pid_t ppid = getppid();
	pid_t pid = getpid();
	const int sh_key = ftok("./oss.c", 0);
	int shm_id = shmget(sh_key, sizeof(int) * 2, IPC_CREAT | 0666);
	int *shm_ptr = shmat(shm_id, 0, 0);
	//printf("key from worker: %d\n", shm_key);
  	printf("worker clock: %d : %d\n", shm_ptr[0], shm_ptr[1]);
	/*int i;
  	for (i = 1; i <= iterations; i++) {
		printf("WORKER PID:%d PPID:%d Iteration:%d before sleeping\n", pid, ppid, i);
 		sleep(1);
		printf("WORKER PID:%d PPID:%d Iteration:%d after sleeping\n", pid, ppid, i);
	}*/
	shmdt(shm_ptr);
	return EXIT_SUCCESS;
}
