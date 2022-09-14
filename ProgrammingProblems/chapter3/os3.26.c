#include <stdio.h>
#include<unistd.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BUFFER_SIZE 100
#define READ_END 0
#define WRITE_END 1

// This program works , but I don't think this is the right way to do it. 
int main(int argc, char* argv[])
{
	if(argc <=1){
		printf("Expecting a string in commandline, Mr.Dumbo!\n");
		return 1;
	}
	
	char* message = argv[1];
	char updated_message[BUFFER_SIZE];
	char new_message[BUFFER_SIZE];
	int fd[2];
	pid_t pid;
	
	// Creating the Pipe
	if(pipe(fd) == -1)
	{
		fprintf(stderr, "Sorry, Pipe creation failed\n");
		return 1;
	}
	
	write(fd[WRITE_END], message, strlen(message) +1 );
	pid = fork();
	if(pid < 0)
	{
		fprintf(stderr, "Sorry, Forking failed\n");
		return 1;
	}
	else if(pid == 0)
	{
		read(fd[READ_END], updated_message, BUFFER_SIZE);
		close(fd[READ_END]);
		int i;
		for(i=0; updated_message[i]!='\0';i++)
		{
			if((updated_message[i] >= 'a') && (updated_message[i] <='z'))
			{
				updated_message[i] = ('A' + updated_message[i] - 'a');
			}
			else if((updated_message[i] >= 'A') && (updated_message[i] <='Z'))
			{
				updated_message[i] = ('a' + updated_message[i] - 'A');
			}
			
		}
		write(fd[WRITE_END], updated_message, BUFFER_SIZE);
		close(fd[WRITE_END]);
		return 0;
	}
	else 
	{
		wait(NULL);
		read(fd[READ_END], new_message, strlen(message) + 1);
		printf("%s\n", new_message);
	}
	return 0;
}
