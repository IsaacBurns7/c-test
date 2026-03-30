#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(){
	int fd = open("p6.txt", O_CREAT | O_WRONLY, 0644); 
	if(fd < 0){
		perror("open failed");
		return 1;
	}
	write(fd, "START\n", 6);
	pid_t pid = fork();
	if(pid == 0){
		for(int i = 0;i<5;i++){
			write(fd, "child\n", 6);
			usleep(1000);
		}
	}else{
		for(int i = 0;i<5;i++){
			write(fd, "parent\n", 7);
			usleep(1000);
		}
	}
	close(fd);
	return 0;
}
