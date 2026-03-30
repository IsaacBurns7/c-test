#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    char c1, c2, c3;
    char *fname = "file.txt";

    int fd1 = open(fname, O_RDONLY);
    int fd2 = open(fname, O_RDONLY);
    int fd3 = open(fname, O_RDONLY);
    if (fd1 < 0 || fd2 < 0 || fd3 < 0) {
        perror("open");
        exit(1);
    }

    // Make fd3 refer to the same open file description as fd2
    if (dup2(fd2, fd3) < 0) {
        perror("dup2");
        exit(1);
    }

    if (read(fd1, &c1, 1) != 1 ||
        read(fd2, &c2, 1) != 1 ||
        read(fd3, &c3, 1) != 1) {
        perror("read");
        exit(1);
    }

    printf("c1 = %c, c2 = %c, c3 = %c\n", c1, c2, c3);

    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}
