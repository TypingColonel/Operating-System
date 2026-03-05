#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
	int pid, shm;
	char *ptr;
	shm = shmget(IPC_PRIVATE, 1024, 0666 | IPC_CREAT);

	pid = fork();

	if (pid > 0) {
		ptr = (char*) shmat(shm, NULL, 0);
		strcpy(ptr, "Hello this is sanjay\n");
		printf("Message shared to shared memory %s\n", ptr);
		shmdt(ptr);
	} else if (pid == 0) {
		sleep(1);
		ptr = (char*) shmat(shm, NULL, 0);
		printf("Message %s\n", ptr);
		shmdt(ptr);
	} 

	shmctl(shm, IPC_RMID, NULL);
	return 0;
} 
