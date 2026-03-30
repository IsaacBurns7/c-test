#include <sys/stat.h>
#include <stdio.h>


int main(){
	struct stat sb;
	stat("/usr/bin/sudo", &sb);

	if (S_ISREG(sb.st_mode)) {
	    printf("Regular file\n");
	}
	if (sb.st_mode & S_ISUID) {
	    printf("Setuid bit is set\n");
	}
	
	struct stat sb2; 
	stat("file.txt", &sb2);
	chmod("file.txt", sb2.st_mode | S_IXUSR | S_IXGRP);
}
