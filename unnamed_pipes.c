#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int fd[2];
	int pid;

	char send_message[] = "Hello this is the parent speaking";
	char read_message[100];
	pipe(fd);
	pid = fork();

	if (pid > 0) {
		close(fd[0]);
		if (write(fd[1], send_message, strlen(send_message) + 1) == -1) {
			printf("Error sending message terminating\n");
			exit(1);
		}

		close(fd[1]);
	} else if (pid == 0) {
		close(fd[1]);
		read(fd[0], read_message, sizeof(read_message));
		printf("Message received: %s", read_message);
		close(fd[0]);
	} 

	return 0;
}
