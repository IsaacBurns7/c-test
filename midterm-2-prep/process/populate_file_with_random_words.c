#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 10

void random_word(char* buf){
	int len = 1 + rand() % MAX_WORD_LEN;
	for(int i = 0; i < len; i++){
		buf[i] = 'a' + rand() % 26;
	}
	buf[len] = '\0';
}

int main(int argc, char *argv[]){
	if(argc < 3){
		printf("Usage: %s <file_str> <size_in_bytes>\n", argv[0]);
		return 1;
	}
	char* file_str = argv[1];
	long int target_size = atol(argv[2]);
	if(target_size <= 0){
		printf("Target_size must be greater than 0. Target size given: %ld\n", target_size);
	}

	srand(time(NULL));
	
	FILE *fp = fopen(file_str, "w");
	if(!fp){
		printf("Could not open file %s", file_str);
		return 1;;
	}

	long int current_size = 0;
	char word[MAX_WORD_LEN+1];

	while(current_size < target_size){
		random_word(word);
		int written = fprintf(fp, "%s ", word);
		if(written < 0){
			printf("Write failed on current_size = %ld\n", current_size);
			return 1;
		}
		current_size += written;
	}
	fclose(fp);
	printf("%s populated with %ld bytes of random words.\n", file_str, current_size);
	return 0;
}
