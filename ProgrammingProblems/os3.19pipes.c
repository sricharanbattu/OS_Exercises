#include <stdio.h>
#include<unistd.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


#define READ_END 0
#define WRITE_END 1
int main(int argc, char* argv[])
{
	pid_t pid;
	struct timeval current_time;
	struct timeval end_time;	

	int fd[2];
	if(pipe(fd) == -1)
	{
		fprintf(stderr, "Pipe failed\n");
		return 1;
	}
	pid = fork();
	
	
	if(pid < 0)
	{
	    fprintf(stderr, "Not forked\n");
	    return 1;
	}
	else if (pid == 0) //child process
	{
	    
	    gettimeofday(&current_time, NULL);
	    //printf("%ld \t %ld\n", current_time.tv_sec, current_time.tv_usec);
	    close(fd[READ_END]);
	    write(fd[WRITE_END], &current_time, sizeof(struct timeval));
	    close(fd[WRITE_END]);
	    execlp(argv[1], argv[1], NULL);
	    
	    return 0;
	}
	else
	{
	    wait(NULL);
	    gettimeofday(&current_time, NULL);
	    //printf("%ld \t %ld\n", current_time.tv_sec, current_time.tv_usec);
	    close(fd[WRITE_END]);
	    read(fd[READ_END], &end_time, sizeof(struct timeval));
	    close(fd[READ_END]);
	    printf("Time taken = %f sec\n", (current_time.tv_sec - end_time.tv_sec) + (current_time.tv_usec - end_time.tv_usec)*10e-6 );
	    
	    
	}
	return 0;
}
