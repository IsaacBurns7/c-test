#include <stdio.h>      // for printf
#include <stdlib.h>     // for exit(), EXIT_SUCCESS
#include <unistd.h>     // for sleep()
#include <signal.h>     // for signal(), SIGQUIT, SIGINT

int s = 0;

static void sig_quit(int signo) {
    printf("In sig_quit, s=%d. Now sleeping...\n", ++s);
    sleep(5);
    printf("sig_quit, s=%d: exiting\n", s);
}

static void sig_int(int signo) {
    printf("Now in sig_int, s=%d. Returning immediately.\n", ++s);
}

int main(void) {
    printf("\n=> Establishing initial signal handlers via signal.\n");

    signal(SIGQUIT, sig_quit);
    signal(SIGINT, sig_int);
	
    raise(SIGINT);
    sleep(5);

    printf("Now exiting.\n");
    exit(EXIT_SUCCESS);
}
