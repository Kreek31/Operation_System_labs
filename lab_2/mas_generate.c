#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char* argv[]){
	if (argc != 2){
		printf("there must be one argument\n");
		return 1;
	}
	srand(time(NULL));
	int len = strtol(argv[1], NULL, 10);
	FILE * filestream = fopen("mas", "w");
	fprintf(filestream, "%d\n", len);
	for (int i = 0; i < len; ++i){
		fprintf(filestream, "%d ", rand()%(rand()%1000));
		srand(rand());
	}
	return 0;
}
