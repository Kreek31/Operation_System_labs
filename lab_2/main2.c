#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>

void* streamFunc();
int recursionSort();
void mergeSort();
int swapFunc();

int main(int argc, char *argv[]){
	time_t start = clock();
	time_t end;
	if (argc != 2){
		printf("error: wrong number of arguments\n");
		return -1;
	}
	FILE * readmas = fopen("mas", "r");
	int streams = strtol(argv[1], NULL, 10);
	int actual_len;
	int formal_len = 1;
	int for_counter;
	int inheritable_streams_one = streams/2;
	int inheritable_streams_two = streams-inheritable_streams_one;
	int len_1 = 0;
	int len_2 = 0;
	pthread_t stream_one;
	pthread_t stream_two;
	
	fscanf(readmas, "%d", &actual_len);
	for (formal_len; formal_len < actual_len; formal_len *= 2);
	int mas[formal_len];
	int returned_mas_1[formal_len/2];
	int returned_mas_2[formal_len/2];
	int* args_one[] = {&len_1, returned_mas_1, &inheritable_streams_one};
	int* args_two[] = {&len_2, returned_mas_2, &inheritable_streams_two};
			
	for (for_counter = 0; for_counter < actual_len; ++for_counter){
		fscanf(readmas, "%d", &mas[for_counter]);
		printf("%d ", mas[for_counter]);
	}
	for (for_counter; for_counter < formal_len; ++for_counter){
		mas[for_counter] = -1;
		printf("%d ", mas[for_counter]);
	}
	printf("\n\n");
	printf("streams:%d\n", streams);
	if (streams > 1) {
		for (int index = 1; index < formal_len; index += 2){
			returned_mas_1[len_1] = mas[index-1];
			returned_mas_2[len_2] = mas[index];
			++len_1;
			++len_2;
		}
		pthread_create(&stream_one, NULL, streamFunc, args_one);
		pthread_create(&stream_two, NULL, streamFunc, args_two);
		pthread_join(stream_two, NULL);
		pthread_join(stream_one, NULL);
		mergeSort(len_1, len_2, returned_mas_1, returned_mas_2, mas);
	} else {
		recursionSort(formal_len, mas);
	}
	printf("\nFirst 'sorted' 20 elements:\n");
	for (for_counter = 0; for_counter < formal_len && for_counter < 20; ++for_counter){
		printf("%d ", mas[for_counter]);
	}
	end = clock();
	printf("\nProgramm worked:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}



void* streamFunc(int *args[]){
	int len = *args[0];
	int* target_mas = args[1];
	int streams = *args[2];
	if (streams > 1){
		int len_1 = 0;
		int len_2 = 0;
		int returned_mas_1[len/2];
		int returned_mas_2[len/2];
		int inheritable_streams_one = streams/2;
		int inheritable_streams_two = streams-inheritable_streams_one;
		int* args_one[] = {&len_1, returned_mas_1, &inheritable_streams_one};
		int* args_two[] = {&len_2, returned_mas_2, &inheritable_streams_two};
		pthread_t stream_one;
		pthread_t stream_two;
		
		for (int index = 1; index < len; index += 2){
			returned_mas_1[len_1] = target_mas[index-1];
			returned_mas_2[len_2] = target_mas[index];
			++len_1;
			++len_2;
		}
		pthread_create(&stream_one, NULL, streamFunc, args_one);
		pthread_create(&stream_two, NULL, streamFunc, args_two);
		pthread_join(stream_two, NULL);
		pthread_join(stream_one, NULL);
		mergeSort(len_1, len_2, returned_mas_1, returned_mas_2, target_mas);
	} else {
		recursionSort(len, target_mas);
	}
}



int recursionSort(int len, int* mas){
	printf("started\n");
	if (len == 2){
		swapFunc(&mas[0], &mas[1]);
		printf("minimas:%d  %d\n", mas[0], mas[1]);
		return 0;
	} else {
		int len_1 = len/2;
		int len_2 = len/2;
		int index_1 = 0;
		int index_2 = 0;
		int returned_mas_1[len_1];
		int returned_mas_2[len_2];
		
		for (int index = 1; index < len; index += 2){
			returned_mas_1[index_1] = mas[index-1];
			returned_mas_2[index_2] = mas[index];
			++index_1;
			++index_2;
		}
		recursionSort(len_1, returned_mas_1);
		recursionSort(len_2, returned_mas_2);
		printf("ended\n");
		mergeSort(len_1, len_2, returned_mas_1, returned_mas_2, mas);
		printf("sorted\n");
		for (int index = 0; index < len; index++){
			printf("i(%d):%d  ", index, mas[index]);
		}
		printf("\n");
		return 0;
	}
}


void mergeSort(int len_1, int len_2, int* mas_1, int* mas_2, int* final_mas){
	int index_1 = 0;
	int index_2 = 0;
	int len = len_1 + len_2;
	for (int index = 0; index < len; index++){
		printf("ind1:%d  ind2:%d  ind:%d\n", index_1, index_2, index);
		if (index_1 >= len_1){
			final_mas[index] = mas_2[index_2];
			++index_2;
		} else if (index_2 >= len_2){
			final_mas[index] = mas_1[index_1];
			++index_1;
		} else {
			if (mas_1[index_1] < mas_2[index_2]){
				final_mas[index] = mas_1[index_1];
				++index_1;
			} else {
				final_mas[index] = mas_2[index_2];
				++index_2;
			}
		}
	}
}



int swapFunc(int *elem1, int *elem2){
	int buffer;
	if (*elem1 > *elem2){
		buffer = *elem1;
		*elem1 = *elem2;
		*elem2 = buffer;
	}
}



