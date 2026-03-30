#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void) {
    char c;
    int myfd = open("file.txt", O_RDONLY);
    if (myfd < 0) {
        perror("open");
        exit(1);
    }

    fork();

    if (read(myfd, &c, 1) != 1) {
        perror("read");
        exit(1);
    }

    printf("Got %c\n", c);
    return 0;
}
