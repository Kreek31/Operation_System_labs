#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>

	const int STDIN_STREAM_NUMBER = 0;
	const int STDOUT_STREAM_NUMBER = 1;

int main(int argc, char* argv[]){
	int number_of_parameters = strtol(argv[1], NULL, 10);
	int pipe_buffer_from_child_to_stdout[2];
	int pipe_buffer_from_father_to_child[2];
	int pipe_buffer_from_child_to_father[2];
	char* pipe_input = malloc(100);
	char* filename = argv[2];
	int i = 0;
	FILE * filestream = fopen(filename, "w");
	
	pipe_buffer_from_child_to_father[1] = number_of_parameters%10;
	number_of_parameters /= 10;
	pipe_buffer_from_child_to_father[0] = number_of_parameters%10;
	number_of_parameters /= 10;
	pipe_buffer_from_father_to_child[1] = number_of_parameters%10;
	number_of_parameters /= 10;
	pipe_buffer_from_father_to_child[0] = number_of_parameters%10;
	
	pipe(pipe_buffer_from_child_to_stdout);
	close(pipe_buffer_from_father_to_child[1]);
	close(pipe_buffer_from_child_to_father[0]);
	close(pipe_buffer_from_child_to_stdout[0]);
	dup2(pipe_buffer_from_father_to_child[0], STDIN_STREAM_NUMBER);
	dup2(pipe_buffer_from_child_to_stdout[1], STDOUT_STREAM_NUMBER);
	do{	
		read(pipe_buffer_from_father_to_child[0], pipe_input, 100);
		if (isupper(pipe_input[0])){
			fprintf(filestream, "%s", pipe_input);
		} else if (*pipe_input != '\0') {
			write(pipe_buffer_from_child_to_father[1], "1", 1);
			close(pipe_buffer_from_father_to_child[0]);
			close(pipe_buffer_from_child_to_father[1]);
			close(pipe_buffer_from_child_to_stdout[1]);
			fclose(filestream);
			return -1;
		}
		write(pipe_buffer_from_child_to_father[1], "0", 1);
	} while(*pipe_input != '\0');
	close(pipe_buffer_from_father_to_child[0]);
	close(pipe_buffer_from_child_to_father[1]);
	close(pipe_buffer_from_child_to_stdout[1]);
	fclose(filestream);
	printf("child process succesfully end work\n");
	return 0;
}









