#include <stdio.h>      // printf
#include <fcntl.h>      // open, O_RDONLY
#include <unistd.h>     // read, close

int main(){
	int fd = open("data.txt", O_RDONLY);
	char buf[10];
	int n = read(fd, buf, 10);
	printf("%d\n", n);
}
