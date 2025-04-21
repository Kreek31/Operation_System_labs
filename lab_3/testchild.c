#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<fcntl.h>



int main(int argc, char* argv[]){
	printf("printing1\n");
	kill(0, SIGUSR1);
	printf("printing2\n");
	return 0;
}


