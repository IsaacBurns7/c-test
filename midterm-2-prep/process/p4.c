#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

#define BUF_SIZE 1024

void sigpipe_handler(int sig){
	printf("Received SIGPIPE!\n");
}

int main(){
	int fd[2];
	pipe(fd);
	signal(SIGPIPE, sigpipe_handler);

	pid_t pid = fork();
	if(pid == 0){
		close(fd[1]); //write end
		char buf[BUF_SIZE];
		int count = 0;
		while(1){
			int n = read(fd[0], buf, BUF_SIZE);
			if(n <= 0) break;
			count++;
			printf("Reader read %d bytes\n", n);
			sleep(1); //slow reader
			//if(count == 5) exit(0); //the read end of the pipe will close... so the writer will cause SIGPIPE
		}
		close(fd[0]);
		exit(0);
	}else{
		close(fd[0]); //read end
		char buf[BUF_SIZE]; 
		memset(buf, 'A', BUF_SIZE);
		int count = 0;
		while(1){
			int n = write(fd[1], buf, BUF_SIZE);
			if(n == -1){
				perror("Write failed.\n");
				break;
			}
			count++;
			printf("Writer wrote chunk %d\n", count);
			if(count == 100){
				printf("Closing write end test soon...\n");
				sleep(1);
			}
		}
		close(fd[1]);
	}
}
