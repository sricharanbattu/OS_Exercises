#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	printf("We are in exe1.c \n PID of exe1.c = %d\n", getpid());
	char* args[] = {"Hello", "ra!", "charan", "NULL"};
	execv("./exe2", args);
	printf("Back to exe1.c\n");
	return 0;
}
