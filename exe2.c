#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	printf("We are in exe2.c \n PID of exe2.c = %d\n", getpid());
	char* args[] = {"Hello", "ra!", "Charan", NULL};
	//execv("./exe1", args);
	//printf("Back to exe2.c\n");
	return 0;
}
