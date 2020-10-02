#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>
#include <signal.h>

#include <sys/wait.h>

void sigHandler(int signo)
{
	if(signo == SIGCHLD)
	{
		printf("%s\n", "SIGCHLD Catched");
	}
}

int main()
{
	pid_t pid;
	int local = 20;

	printf("%s\n", "Signal Handler");
	if(signal(SIGCHLD, sigHandler) == SIG_ERR)
	{
		perror("signal(): SIGCHLD");
		return -1;
	}

	if((pid = fork()) < 0)
	{
		printf("%s\n", "ERROR : fork()");
	}
	else if(pid == 0)
	{
		printf("\nChild Part\n");
		printf("Return Value: %d\n", pid);
		printf("My PID: %d, Parent PID: %d\n", getpid(), getppid());
		printf("Local Variable: %d\n", local);
		sleep(2);
	}
	else
	{
		int status;
		printf("\nParent Part\n");
		printf("Return Value: %d\n", pid);
		printf("My PID: %d, Parent PID: %d\n", getpid(), getppid());
		printf("Local Variable: %d\n", local);
		wait(&status);
	}

	printf("Common\n");


	return 0;
}