#include <stdio.h>

int main(){
	int i = 0;
	for(i = 0 ; i < 1024; i ++){
		int * pointer = malloc((size_t) i * 1024);
		free(pointer);
	}
	return 0;
}
