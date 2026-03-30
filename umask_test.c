#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(){
	int fd = open("newfile.txt", O_CREAT | O_WRONLY, 0644);
}
