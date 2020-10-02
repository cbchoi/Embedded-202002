#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	int local = 20;

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
	}
	else
	{
		printf("\nParent Part\n");
		printf("Return Value: %d\n", pid);
		printf("My PID: %d, Parent PID: %d\n", getpid(), getppid());
		printf("Local Variable: %d\n", local);
		sleep(1);
	}

	printf("Common\n");

	return 0;
}