#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>
int main(void)
{
	int status;
	pid_t killReturnVal, forkReturnVal;
	forkReturnVal=fork();
	if(forkReturnVal<0)
	{
		printf("Error !!");
		exit(EXIT_FAILURE);
	}
	if(forkReturnVal==0)
	{
		sleep(100);
		exit(EXIT_SUCCESS);
	}
	else
	{
		killReturnVal=kill(forkReturnVal,SIGKILL);
		if(killReturnVal)
		{
			printf("ChildProcess Can't be Killed \n");
			waitpid(forkReturnVal,&status,0);
		}
		else
		{
			printf("[+]+ Killed    Child Process got Terminated \n");
		}
	}
	return 0;
}