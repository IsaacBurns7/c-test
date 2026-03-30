#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
  int fd;
  char *fname = "foo";

  fd = open(fname, O_CREAT|O_TRUNC|O_WRONLY, S_IRWXU);
  write(fd, "pqrs", 2);
  write(fd, "jklmn", 6);

  close(fd);
  return 0;
}
