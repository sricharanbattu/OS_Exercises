#include <stdio.h>
#include<unistd.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[])
{

	printf("Child started\n");
	int fd;
	const int SIZE = 400;
	const char* SHARED_OBJ = "COLLATZ";
	fd = shm_open(SHARED_OBJ, O_RDWR, 0666);
	if(fd < 0)
	{
		fprintf(stderr, "Unable to open Shared Memory Object ");
		return 1;
	}
	
	int *ptr = (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
	int x = atoi(argv[0]);
	if(x < 1)
		return 0;
	while( x > 1)
	{

		*(ptr++) = x;
		
		if(x%2 == 0)
			x = x/2;
		else
			x = (3*x) + 1;
	}
	*(ptr++) = x;
	shm_unlink(SHARED_OBJ);
	printf("Child about to complete\n");
	return 0;
}
