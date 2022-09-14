#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	pid = fork();
	
	if(pid < 0)
	{
		fprintf(stderr, "Fork failed\n");
		return 1;
	}
	else if(pid ==0 )
	{
		return 0;
	}
	else
	{
		sleep(10);
		wait(NULL);
		printf("Child terminates now.\n");
	}
	return 0;
}
