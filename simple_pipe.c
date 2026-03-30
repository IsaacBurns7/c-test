#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>

void simple_pipe(char* cmd1, char** argv1, char* cmd2, char** argv2){
	int pipefd[2], r, status;
	//A
	pipe(pipefd);

	pid_t child1 = fork();
	if(child1 == 0){
		//B
		//dup2(pipefd[1], STDOUT_FILENO) -> stdout and pipefd[1] both exist in process FD Table, and they both have entries pointing to OFD objects in the kernel. kernel_OFD[stdout] = <X>, kernel_OFD[pipefd[1]] = write end of the unix pipe we just created. stdout is closed in the process FD table, decrementing the reference count of the kernel OFD it was pointing at, which if it is now 0, will be destroyed. Then kernel_OFD[stdout] = write end of the pipe.
		dup2(pipefd[1], STDOUT_FILENO);
		//close(pipefd[0]); 
		//close(pipefd[1]);
		execvp(cmd1, argv1);
	}
	assert(child1 > 0);
	//C
	pid_t child2 = fork();
	if(child2 == 0){
		dup2(pipefd[0], STDIN_FILENO);
		//close(pipefd[0]); 
		//close(pipefd[1]);
		execvp(cmd2, argv2);
	}
	close(pipefd[0]); close(pipefd[1]);
	r = waitpid(child1, &status, 0);
	r = waitpid(child2, &status, 0);
}

int main(void) {
    /* Test 1: ls | wc -l */
    char *argv1_ls[] = {"ls", NULL};
    char *argv2_wc[] = {"wc", "-l", NULL};
    simple_pipe("ls", argv1_ls, "wc", argv2_wc);

    /* Test 2: ps aux | grep root */
    char *argv1_ps[] = {"ps", "aux", NULL};
    char *argv2_grep[] = {"grep", "root", NULL};
    simple_pipe("ps", argv1_ps, "grep", argv2_grep);

    /* Test 3: echo hello world | tr a-z A-Z */
    char *argv1_echo[] = {"echo", "hello world", NULL};
    char *argv2_tr[] = {"tr", "a-z", "A-Z", NULL};
    simple_pipe("echo", argv1_echo, "tr", argv2_tr);

    /* Test 4: cat /etc/passwd | wc -l */
    char *argv1_cat[] = {"cat", "/etc/passwd", NULL};
    char *argv2_wc2[] = {"wc", "-l", NULL};
    simple_pipe("cat", argv1_cat, "wc", argv2_wc2);

    return 0;
}


