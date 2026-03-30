#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main () {
  int fd = open ("test.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
  if (fd < 0) {
    perror ("Cannot create file ");
    exit (0);
  }
  printf("File created successfully\n");
}
