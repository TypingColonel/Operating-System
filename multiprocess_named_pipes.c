#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main () {

	int fd, pid;
	char write_message[] = "hello sanjay"; 
	char read_message[50];

	mkfifo("named_pipe", 0666);
	pid = fork();

	if (pid > 0) {
		fd = open("named_pipe", O_WRONLY);
		write(fd, write_message, strlen(write_message) + 1);
		printf("Message has been written into the pipe\n");
		close(fd);
	} else if (pid == 0) {
		fd = open("named_pipe", O_RDONLY);
		read(fd, read_message, sizeof(read_message));
		printf("Message received from writer via pipe\nMessage as follows: %s\n", read_message);
		close(fd);
	} 

	return 0;
}
	
