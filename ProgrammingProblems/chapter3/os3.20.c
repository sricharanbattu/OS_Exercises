#include <stdio.h>
#include<unistd.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>

#define MINPID 300
#define MAXPID 5000

char* bitmap; 

int allocate_bitmap(void)
{
	int size = ((MAXPID - MINPID +1)/8) + 1;
	int i;
	bitmap = (char* )malloc(size);
	
	if(bitmap == NULL)
		return -1;
	else
	{
		for(i=0;i<size;i++)
		{
			bitmap[i] = 0; 
		}
	}
	return 1;
	
}

int allocate_pid(void)
{
	int size = ((MAXPID - MINPID +1)/8) + 1;
	int i=0;
	for(i=0;i<(size-1);i++)
	{
		char c = bitmap[i];
		for(int j=0;j<8;j++)
		{
			if(!(c&(1<<j)))
			{
				bitmap[i] |= (1<<j);
				return (i*8) + j + MINPID;
				
			}
		}
	}
	
	char c = bitmap[i];
	for(int j=0;j<(size%8);j++)
	{
		if(!(c&(1<<j)))
		{
			bitmap[i] |= (1<<j);
			return (i*8) + j + MINPID;
		}
	}
	
	return -1;
}

void release_pid(int pid)
{
	if((pid < MINPID) || (pid > MAXPID))
	{
		printf("wrong pid Given\n");
		return;
	}
	pid -= MINPID; 
	int byte_loc = pid/8;
	int bit_loc = pid%8;
	
	bitmap[byte_loc] &= ~(1<<bit_loc);
	return;
}

void destoy_bitmap(void){
	free(bitmap);
}

int main()
{
	
	int status = allocate_bitmap();
	if(status < 0)
	{
		printf("unable to allocate bitmap\n");
	}
	
	int pid = allocate_pid();
	printf("%d\n", pid);
	pid = allocate_pid();
	printf("%d\n", pid);
	release_pid(pid);
	printf("%d\n", bitmap[0]);
	destroy_bitmap();
	return 0;
}
