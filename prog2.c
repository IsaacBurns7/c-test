#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	char* argv[2];
	argv[0] = (char *)"prog1";
	argv[1] = NULL;

	printf("PID %d running prog2(parent before fork)\n", getpid());

	pid_t pid = fork();

	if(pid == 0){
		execv("./prog1", argv);
		perror("execv failed");
		return 1;
	}else{
		waitpid(pid, NULL, 0);
		printf("PID %d exiting from prog2(parent after wait)\n", getpid());
	}
	return 0;
}
