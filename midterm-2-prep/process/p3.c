#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

void block_signals(sigset_t *set){
	if(sigprocmask(SIG_BLOCK, set, NULL) == -1){
		perror("sigprocmask block failed");
		exit(1);
	}
}

void unblock_signals(sigset_t *set){
	if(sigprocmask(SIG_UNBLOCK, set, NULL) == -1){
		perror("sigprocmask unblock failed");
		exit(1);
	}
}

//retries if interrupted by signals
ssize_t robust_read(int fd, void *buf, size_t count){
	ssize_t n;
	while(1){
		n = read(fd, buf, count);
		if(n == -1){
			if(errno = EINTR){
				continue; //interrupted by signal
			}else{
				perror("read failed");
				return -1;
			}
		}
		break; //read succeeded
	}
	return n;
}

int main(int argc, char *argv[]){
	if(argc < 3){
		printf("Usage: %s <in_file_str> <out_file_str>\n", argv[0]);
		return 1;
	}
	char* in_file_str = argv[1];
	int in_fd = open(in_file_str, O_RDONLY);
	if(in_fd == -1){
		perror("open failed");
		exit(1);
	}
	char* out_file_str = argv[2];
	int out_fd = open(out_file_str, O_WRONLY | O_CREAT, 0700);
	if(out_fd == -1){
		perror("open failed");
		exit(1);
	}
	
	char buf[1024];

	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT); //block ctrl-c temporarily
	while(1){
		block_signals(&set);
		ssize_t n = robust_read(in_fd, buf, sizeof(buf));
		unblock_signals(&set);

		if(n > 0){
			printf("Read %zd bytes successfully to %s.\n", n, out_file_str);
			ssize_t n_written = write(out_fd, buf, n);
			if(n_written == -1){
				perror("Write failed");
				break;
			}
		}else if (n==0){
			printf("Reached EOF.\n");
			break;
		}else{
			printf("Error reading from file.\n");
			break;
		}
	}
	close(in_fd);
	close(out_fd);
	return 0;
}
