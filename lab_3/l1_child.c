#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<ctype.h>
#include<stdbool.h>

void continuation(int){
	//printf("continuation\n");
}

void ending(int){
	printf("ending child process\n");
	exit(0);
}

int main(int argc, char* argv[]){
	signal(SIGUSR1, continuation);
	signal(SIGUSR2, ending);
	signal(SIGTERM, ending);
	char* filename = argv[1];
	int mmap_file = atoi(argv[2]);
	char* mmap_pointer;
	int offset;
	int iterator;
	int readlen = 10;
	FILE* file_stream = fopen(filename, "w");

	while(1){
		pause();
		
		//printf("%s\n", filename);
		offset = 0;
		mmap_pointer = mmap(0, readlen, PROT_WRITE, MAP_SHARED, mmap_file, offset);
		if (isupper(mmap_pointer[0]) == false){
			kill(0, SIGTERM);
		}
		iterator = 0;
		while(mmap_pointer[iterator] != '\0'){
			printf("writing:%c    ", mmap_pointer[iterator]);
			fprintf(file_stream, "%c", mmap_pointer[iterator]);
			++iterator;
			printf("%d - %d\n", iterator, readlen);
			if (iterator >= readlen+offset){
				printf("changing offset\n");
				offset += readlen;
				mmap_pointer = mmap(0, readlen+offset, PROT_WRITE, MAP_SHARED, mmap_file, 0);
				printf("offset changed. Next letter:%c\n", mmap_pointer[iterator]);
			}
		}
		kill(0, SIGUSR1);
	}
	printf("\nfilename:%s\n", filename);
	printf("\ndescriptor:%d\n", mmap_file);
	printf("\nfirst char:%c\n", mmap_pointer[0]);
	return 0;
}









