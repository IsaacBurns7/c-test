#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUF_SIZE 1024

void sigpipe_handler(int sig){
	printf("Received SIGPIPE!\n");
}

int main(){
	int fd = open("temp.txt", O_CREAT | O_WRONLY, 0644);;
	if(fd == -1) { perror("open failed"); exit(1); }
	printf("Before exec: PID=%d, FD=%d\n", getpid(), fd);
	// Optional: make fd close-on-exec to test effect
    	fcntl(fd, F_SETFD, FD_CLOEXEC);
	char *args[] = {"./child", NULL}; // child is a separate program that prints PID and FD
	execv(args[0], args);
	perror("execv failed");
	return 1;
}
