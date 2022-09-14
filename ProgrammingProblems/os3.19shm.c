#include <stdio.h>
#include<unistd.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	pid_t pid;
	const int SIZE = 20;	
	int fd;
	
	const char* SHARED_MEM_OBJ = "SHARED";
	fd = shm_open(SHARED_MEM_OBJ, O_CREAT | O_RDWR, 0666);
	ftruncate(fd, SIZE);
	void* ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	
	struct timeval* current_time = ptr;

	pid = fork();
	if(pid < 0)
	{
	    fprintf(stderr, "Not forked\n");
	    return 1;
	}
	else if (pid == 0) //child process
	{
	    
	    gettimeofday(current_time, NULL);
	    execlp(argv[1], argv[1], NULL);
	    
	    return 0;
	}
	else
	{
		
	    wait(NULL);
	    struct timeval end_time;
	    gettimeofday(&end_time, NULL);
	    printf("Time taken = %f sec\n", (end_time.tv_sec - current_time->tv_sec) + (end_time.tv_usec - current_time->tv_usec)*10e-6 );
	    
	    
	}
	return 0;
}
