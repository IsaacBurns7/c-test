#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    int fd1, fd2, fd3;
    char *fname = argv[1];

    fd1 = open(fname, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd1 < 0) { perror("open fd1"); exit(1); }

    if (write(fd1, "pqrs", 4) != 4) { perror("write1"); exit(1); }

    fd2 = open(fname, O_APPEND | O_WRONLY);
    if (fd2 < 0) { perror("open fd2"); exit(1); }

    if (write(fd2, "jklmn", 5) != 5) { perror("write2"); exit(1); }

    fd3 = dup(fd1);  // fd3 shares fd1's open file description
    if (fd3 < 0) { perror("dup"); exit(1); }

    if (write(fd3, "wxyz", 4) != 4) { perror("write3"); exit(1); }

    if (write(fd2, "ef", 2) != 2) { perror("write4"); exit(1); }

    lseek(fd1, 0, SEEK_SET);

    if (write(fd1, "ab", 2) != 2) { perror("write5"); exit(1); }

    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}
