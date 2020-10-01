#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigHandler(int signo)
{
	if(signo == SIGUSR1)
	{
		printf("%s\n", "SIGUSR1 Catched");
	}
	else if(signo == SIGUSR2)
	{
		printf("%s\n", "SIGUSR2 Catched");	
	}
}

int main()
{
	printf("%s\n", "Signal Handler");
	if(signal(SIGUSR1, sigHandler) == SIG_ERR)
	{
		perror("signal(): SIGUSR1");
		return -1;
	}

	if(signal(SIGUSR2, sigHandler) == SIG_ERR)
	{
		perror("signal(): SIGUSR2");
		return -1;
	}

	printf("%s\n", "Waiting for signals");
	while(1) 
		pause();

	return 0;
}