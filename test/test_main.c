#include<stdio.h>
#include<string.h>
#include<readable.h>


int main(int argc, char **argv){
    int out = 0;

	if(argc < 2){
		printf("not enough arguements (function name)\n");
		return(-1);
	}

	if(strcmp(argv[1], "readable") == 0 && argc > 2){
		printf("run the readable function\n");
		out = readable(argv[2]);
		printf("readable returned %d\n", out);
	}else if(strcmp(argv[1], "readable") == 0 && argc == 2){
		printf("run the readable function with NULL path.\n");
		out = readable(NULL);
		printf("readable returned %d\n", out);
	}else{
		printf("no valid test passed.\n");
	}

	return(1);
}