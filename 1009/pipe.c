#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

struct my_msg
{
	int data1;
	int data2;
};

int main()
{
	pid_t pid;
	int pfd[2];
	int status;
	char* buff = malloc(sizeof(struct my_msg));

	if(pipe(pfd) < 0)
	{
		perror("pipe()");
		return -1;
	}

	if((pid = fork()) < 0)
	{
		perror("fork()");
		return -1;
	}
	else if(pid == 0)
	{
		struct my_msg _var;
		_var.data1 = 10;
		_var.data2 = 20;

		printf("%s: data1:%d data2:%d\n", "Child Process", 
			_var.data1, _var.data2);
		write(pfd[1], &_var, sizeof(struct my_msg));
	}
	else
	{
		struct my_msg _var;
		_var.data1 = 20;
		_var.data2 = 10;

		printf("%s: data1:%d data2:%d\n", "Parent Process", 
			_var.data1, _var.data2);
		read(pfd[0], &_var, sizeof(struct my_msg));
			printf("%s: data1:%d data2:%d\n", "After receiving msg from Child Process", 
			_var.data1, _var.data2);
		waitpid(pid, &status, 0);
	}

	free(buff);
	return 0;
}