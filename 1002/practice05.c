#include <stdio.h>

#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int my_system(const char* cmd)
{
	pid_t pid;
	int status;

	if((pid = fork()) < 0)
	{
		status = -1;
	} 
	else if(pid == 0)
	{ /* Child Part*/
		execl("/bin/sh", "sh", "-c", cmd, (char*) 0);
		_exit(127);
	}
	else
	{ /* Parent Part*/
		while(waitpid(pid, &status, 0) < 0)
		{
			if(errno != EINTR)
			{
				status = -1;
				break;
			}
		}
	}
}

int main(int argc, char** argv, char **envp)
{
	printf("-- ENV Variable Start --\n");
	while(*envp)
	{
		printf("%s\n", *envp++);
	}
	printf("-- ENV Variable End --\n");

	my_system("ls -al");
	return 0;
}