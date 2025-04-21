#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>


int main(){
	printf("max size of input is 100 symbols. If input has more symbols, programm may work incorrect. Every input must start with hight letter\n");
	char* filename = malloc(100);
	char* std_input = malloc(100);
	char child_status[1];
	char child_parameters[4];
	int pipe_buffer_from_father_to_child[2];
	int pipe_buffer_from_child_to_father[2];

	printf("input filename to write:");
	scanf("%s", filename);
	if (pipe(pipe_buffer_from_father_to_child) == -1){
		perror("error when creationg pipe");
		return -1;
	} else if (pipe(pipe_buffer_from_child_to_father) == -1){
		perror("error when creationg pipe");
		return -1;
	}
	
	pid_t pid = fork();
	if (pid == -1){
		perror("fork");
		return -1;
	} else if (pid == 0) {
		child_parameters[0] = (pipe_buffer_from_father_to_child[0]+'0');
		child_parameters[1] = (pipe_buffer_from_father_to_child[1]+'0');
		child_parameters[2] = (pipe_buffer_from_child_to_father[0]+'0');
		child_parameters[3] = (pipe_buffer_from_child_to_father[1]+'0');
		execl("./child", "./child", child_parameters, filename, NULL);
	} else {
		close(pipe_buffer_from_father_to_child[0]);
		close(pipe_buffer_from_child_to_father[1]);
		getc(stdin);
		printf("scanning:");
		while (fgets(std_input, 100, stdin)!=NULL && *std_input != '\n') {
			write(pipe_buffer_from_father_to_child[1], std_input, 100);
			read(pipe_buffer_from_child_to_father[0], child_status, 1);
			if (child_status[0] == '1'){
				wait(NULL);
				close(pipe_buffer_from_father_to_child[1]);
				close(pipe_buffer_from_child_to_father[0]);
				printf("error: wrong string format\n");
				return -1;
			}
			printf("scanning:");
		}
		printf("\n");
		write(pipe_buffer_from_father_to_child[1], "\0", 1);
	}
	printf("waiting for end of child process...\n");
	wait(NULL);
	printf("parent process succesfully end work\n");
	return 0;
}








