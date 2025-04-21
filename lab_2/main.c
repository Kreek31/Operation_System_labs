#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>

void* streamFunc();
int* recursionSort();
int swapFunc();
int u = 0;

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
	int stream_one_mas_index = 0;
	int stream_two_mas_index = 1;
	int current_step = 2;
	int swap;
	int first_index = 0;
	int second_index = 1; 
	pthread_t stream_one;
	pthread_t stream_two;
	
	fscanf(readmas, "%d", &actual_len);
	for (formal_len; formal_len < actual_len; formal_len *= 2);
	int mas[formal_len];
	int final_mas[formal_len];
	int* args_one[] = {&current_step, mas, &formal_len, &inheritable_streams_one, &stream_one_mas_index};
	int* args_two[] = {&current_step, mas, &formal_len, &inheritable_streams_two, &stream_two_mas_index};
	int requiring_sort = formal_len;
			
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
		pthread_create(&stream_one, NULL, streamFunc, args_one);
		pthread_create(&stream_two, NULL, streamFunc, args_two);
		end = clock();
		pthread_join(stream_two, NULL);
		pthread_join(stream_one, NULL);
		for (for_counter = 0; for_counter < formal_len-1; ++for_counter){
			swapFunc(&mas[for_counter], &mas[for_counter+1]);
		}
	} else {
		recursionSort(1, mas, formal_len, 0);
		end = clock();
	}
	for (for_counter = 0; for_counter < formal_len; ++for_counter){
		if (mas[first_index] < mas[second_index]){
			final_mas[for_counter] = mas[first_index];
			first_index += 2;
		} else {
			final_mas[for_counter] = mas[second_index];
			second_index += 2;
		}
	}
	printf("\nFirst 'sorted' 20 elements:\n");
	for (for_counter = 0; for_counter < formal_len && for_counter < 20; ++for_counter){
		printf("%d	%d\n", mas[for_counter], mas[for_counter+1]);
	}
	for (for_counter = 0; for_counter < formal_len && for_counter < 20; ++for_counter){
		printf("%d ", final_mas[for_counter]);
	}
	printf("\nProgramm worked:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}



void* streamFunc(int *args[]){
	int swap;
	int step = *args[0];
	int* final_mas = args[1];
	int formal_len = *args[2];
	int first_sort_element = *args[4];
	int streams = *args[3];
	if (streams > 1) {
		pthread_t stream_one;
		pthread_t stream_two;
		int inheritable_streams_one = streams/2;
		int inheritable_streams_two = streams-inheritable_streams_one;
		int stream_one_mas_index = first_sort_element;
		int stream_two_mas_index = first_sort_element+step;
		int returned_mas_1[(formal_len-first_sort_element-1)/(step*2)+1];
		int returned_mas_2[(formal_len-first_sort_element-step-1)/(step*2)+1];
		int* args_one[] = {&step, returned_mas_1, &formal_len, &inheritable_streams_one, &stream_one_mas_index};
		int* args_two[] = {&step, returned_mas_2, &formal_len, &inheritable_streams_two, &stream_two_mas_index};
		
		step *= 2;
		pthread_create(&stream_one, NULL, streamFunc, args_one);
		pthread_create(&stream_two, NULL, streamFunc, args_two);
		pthread_join(stream_two, NULL);
		pthread_join(stream_one, NULL);
		step /= 2;
		
		for (first_sort_element; first_sort_element < formal_len-step; first_sort_element += step){
			swapFunc(&final_mas[first_sort_element], &final_mas[first_sort_element+step]);
		}
	} else{
		recursionSort(step, final_mas, formal_len, first_sort_element);
	}
	return 0;
}



int* recursionSort(int step, int* mas, int formal_len, int first_sort_element, int* final_mas){
	if (step*2 > formal_len/2){
		for (first_sort_element; first_sort_element < formal_len-step; first_sort_element += step){
			swapFunc(&mas[first_sort_element], &mas[first_sort_element+step]);
			printf("swap ");
		}
		printf("\n");
		final_mas[0] = mas[first_sort_element-step];
		final_mas[1] = mas[first_sort_element];
		printf("minimas:%d  %d\n", final_mas[0], final_mas[1]);
		return 0;
	}
	int len_1 = (formal_len-first_sort_element-1)/(step*2)+1;
	int len_2 = (formal_len-first_sort_element-step-1)/(step*2)+1;
	int returned_mas_1[len_1];
	int returned_mas_2[len_2];
	recursionSort(step*2, mas, formal_len, first_sort_element, returned_mas_1);
	recursionSort(step*2, mas, formal_len, first_sort_element+step, returned_mas_2);
	int buffer;
	int returned_mas[len_1+len_2];
	printf("len1:%d len2:%d len:%d\n", len_1, len_2, (formal_len-first_sort_element-1)/step+1);
	int index = 0;
	int index_1 = 0;
	int index_2 = 0;
	while (index_1 < len_1 || index_2 < len_2){
		//printf("ind_1:%d  ind_2:%d\n", index_1, index_2);
		if (index_1 >= len_1){
			final_mas[index] = returned_mas_2[index_2];
			++index_2;
			++index;
		} else if (index_2 >= len_2){
			final_mas[index] = returned_mas_1[index_1];
			++index_1;
			++index;
		} else {
			if (returned_mas_1[index_1] < returned_mas_2[index_2]){
				final_mas[index] = returned_mas_1[index_1];
				++index_1;
				++index;
			} else {
				final_mas[index] = returned_mas_2[index_2];
				++index_2;
				++index;
			}
		}
	}
	for (int i = 0; i < len_1+len_2; i++){
		printf("i(%d):%d  ", i, final_mas[i]);
	}
	printf("\n");
}



int swapFunc(int *elem1, int *elem2){
	int buffer;
	if (*elem1 > *elem2){
		buffer = *elem1;
		*elem1 = *elem2;
		*elem2 = buffer;
	}
}



