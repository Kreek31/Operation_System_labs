#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/mman.h>

int main(){
	int mmap_file = open("mmapfile.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (mmap_file == -1){
		perror("open");
		return -1;
	}
	
	if (ftruncate(mmap_file, 64) == -1){
		perror("ftruncate");
		return -1;
	}
	
	char* mmap_pointer = mmap(0, 64, PROT_WRITE, MAP_SHARED, mmap_file, 0);
	if (mmap_pointer == MAP_FAILED){
		perror("mmap");
		return -1;
	}
	mmap_pointer[0] = 'e';
	
	if (munmap(mmap_pointer, 64) == -1){
		perror("munmap");
		return -1;
	}
	
	close(mmap_file);
}
