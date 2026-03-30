#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char** argv){
	if(argc != 2){
		printf("Usage: %s <number_of_loops>\n", argv[0]);
		return 1;
	}
	int loops = atoi(argv[1]);
	if(loops <= 0){
		printf("Number of loops must be positive\n");
		return 1;
	}
	int count = 0;
	pid_t main_process_pid = getpid();
	for(int i = 0;i < loops;i++){
		pid_t pid = fork();
		if(pid == 0){
			printf("Forked child process as PID: %d, with parent: %d\n", getpid(), getppid());
			exit(0);
		}else if(pid > 0){
			wait(NULL);
			count++;
		}else{
			perror("Fork failed");
		}
	
	}
	if(getpid() == main_process_pid)
		printf("Number of children: %d\n", count);
}
