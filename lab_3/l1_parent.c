#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<fcntl.h>

void filler(int){

}

void inputError(int){
	printf("finishing programm because of input error\n");
	exit(-1);
}

int main(int argc, char* argv[]){
	signal(SIGUSR1, filler);
	signal(SIGUSR2, filler);
	signal(SIGTERM, inputError);
	printf("max size of input is 100 symbols. If input has more symbols, programm may work incorrect. Every input must start with hight letter\n");
	char* filename = malloc(100);
	char* std_input = malloc(100);
	char child_status[1];
	char child_parameters[4];
	char* mmap_pointer;
	int mmap_file = open("mmapfile.txt", O_RDWR | O_TRUNC);
	size_t len;
	
	printf("input filename to write:");
	scanf("%s", filename);
	
	pid_t pid = fork();
	if (pid == -1){
		perror("fork");
		return -1;
	} else if (pid == 0) {
		printf("\n\n\nstarted child process\n");
		char descriptor[1];
		descriptor[0] = mmap_file+'0';
		execl("./child", "./child", filename, descriptor, NULL);
		printf("\n\n\nafg\n\n\n");
		return 0;
	} else {
		getc(stdin);
		printf("scanning:");
		while (fgets(std_input, 100, stdin)!=NULL && *std_input != '\n') {
			len = strlen(std_input);
			if (ftruncate(mmap_file, len) == -1){
				perror("ftruncate");
				return -1;
			}
			mmap_pointer = mmap(0, len, PROT_WRITE, MAP_SHARED, mmap_file, 0);
			if (mmap_pointer == MAP_FAILED){
				perror("mmap");
				return -1;
			}
			printf("string:%s", std_input);
			//printf("%d\n", mmap_pointer);
			for (int i = 0; i < len; i++){
				//printf("writing:%c\n", std_input[i]);
				mmap_pointer[i] = std_input[i];
			}
			printf("signaling\n");
			kill(0, SIGUSR1);
			pause();
			printf("scanning:");
		}
		printf("\n");
	}
	printf("waiting for end of child process...\n");
	kill(0, SIGUSR2);
	wait(NULL);
	printf("parent process succesfully end work\n");
	return 0;
}








