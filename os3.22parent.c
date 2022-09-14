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

	if(argc == 1)
	{
		printf("Expecting an integer in the command line dumbo\n");
		return 1;
	}
	int fd;
	const int SIZE = 400;
	const char* SHARED_OBJ = "COLLATZ";
	
	
	fd = shm_open(SHARED_OBJ, O_CREAT | O_RDWR, 0666);
	if(fd < 0)
	{
		fprintf(stderr, "Unable to open Shared Memory Object ");
		return 1;
	}
	ftruncate(fd, SIZE);
	int *ptr = (int* )mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
	
	
	
	pid_t pid;
	pid = fork();
	
	if(pid < 0)
	{
		fprintf(stderr, "Forking failed\n");
		return 1;
	}
	else if(pid == 0)
	{
		//child Process
		/*int x = atoi(argv[1]);
		while(x != 1)
		{
			*(ptr++) = x;
			if(x%2 ==0)
			{
				x = x>>1;
			}
			else
			{
				x = 3*x + 1;
			}
		}
		
		*(ptr++) = x;
		shm_unlink(SHARED_OBJ);
		return 0;
		*/
		execl("os3.22child", argv[1], NULL);
		return 0;
	}
	else
	{
	
		wait(NULL);
		printf("Entering the parent again\n");
		while((*ptr) != 1)
		{
			printf("%d\n", *(ptr++));
		}
		
		printf("%d\n", *ptr);
		shm_unlink(SHARED_OBJ);
	}
	return 0;
}
