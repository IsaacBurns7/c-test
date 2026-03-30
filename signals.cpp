#include <stdio.h>      // for printf
#include <stdlib.h>     // for exit(), NULL
#include <unistd.h>     // for fork(), sleep()
#include <signal.h>     // for signal(), SIGCHLD
#include <sys/types.h>  // for pid_t
#include <sys/wait.h>   // for wait()
#include <stdlib.h>
#include <time.h>

void my_handler(int sig) {
    pid_t pid = wait(0);
    printf("Child process %d exited.\n", pid);
}

int main() {
    signal(SIGCHLD, my_handler);
	srand(time(NULL));
    // ith process sleeps for i sec and dies
    for (int i = 1; i <= 150; i++) {
        int pid = fork();
        if (pid == 0) {
		int ms = rand() % 10000; // random 100-5100 ms
		struct timespec ts;
		ts.tv_sec = ms / 1000;
		ts.tv_nsec = (ms % 1000) * 1000 * 1000;
		nanosleep(&ts, NULL);
		return 0;  // child exits
        }
    }

    // parent in an infinite busy loop
    while (1) {
        printf("Relaxing\n");
        sleep(1);
    }

    return 0;
}
