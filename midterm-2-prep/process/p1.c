#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>


int main(int argc, char *argv[]){
	srand(time(NULL));
	if(argc < 3){
		printf("Usage: %s <number_of_children> <kill_chance>\n", argv[0]);
		printf("Example: %s 5 0.3 #5 children, 30%% chance for parent to kill\n", argv[0]);
		return 1;
	}

	int num_children = atoi(argv[1]);
	float kill_chance = atof(argv[2]);
	if(num_children <= 0 || kill_chance < 0.0 || kill_chance > 1.0){
		printf("Invalid args. num_children > 0, kill_chance in range [0.0, 1.0]. Given num_children:%d and kill_chance:%f\n", num_children, kill_chance);
		return 1;
	}
	pid_t pids[num_children];
	
	printf("BEGINNING PROBLEM1(Spawn X children, kill randomly with Y chance) SIMULATION with num_children=%d, kill_chance=%f\n", num_children, kill_chance);
	fflush(stdout); //make sure buffer is written before fork();

	for(int i = 0;i<num_children;i++){
		pid_t pid = fork();
		if(pid < 0){
			perror("fork failed");
			exit(1);
		}else if(pid == 0){
			printf("Child %d: PID=%d, parent PID=%d\n", i, getpid(), getppid());
			sleep(3 + rand() % 3); //3-5 sec work
			printf("Child %d: finished work.\n", i);
			exit(i); 
		}else{
			pids[i] = pid;
		}
	}
	
	sleep(1);
	for(int i = 0;i<num_children;i++){
		float r = (float)rand() / RAND_MAX; //random float between 0 and 1
		if(r < kill_chance){
			printf("Parent %d: Randomly killing child %d PID=%d (random chance %.2f < %.2f)\n", getpid(), i, pids[i], r, kill_chance);
		       	kill(pids[i], SIGKILL);	
		}else{
			printf("Parent %d: Randomly sparing child %d PID=%d (random chance %.2f >= %.2f)\n", getpid(), i, pids[i], r, kill_chance);
		}
	}
	
	for(int i = 0;i<num_children;i++){
		int status; 
		waitpid(pids[i], &status, 0);
		if(WIFEXITED(status)){
			printf("Parent: My PID is %d, and my child %d PID=%d exited with code %d\n", getpid(), i, pids[i], WEXITSTATUS(status));
		}else if(WIFSIGNALED(status)){
			printf("Parent: My PID is %d, and my child %d PID=%d was killed by signal %d\n", getpid(), i, pids[i], WTERMSIG(status));
		}
	}
	return 0;
}

