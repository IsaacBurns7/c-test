#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int fd = 3; // assume parent’s FD is 3

    if (write(fd, "Hello\n", 6) == -1) {
        perror("write to FD 3 failed");
    } else {
        printf("Wrote to FD 3 successfully!\n");
    }

    printf("Child PID=%d\n", getpid());
    return 0;
}
