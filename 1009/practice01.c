#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

struct my_msg
{
	int data1;
	int data2;
};

int main()
{
	pid_t pid;
	int status;
	int pfd[2];

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
		struct my_msg _val;
		_val.data1 = 10;
		_val.data2 = 11;

		printf("[%s] data1:%d, data2:%d\n", "Child Process",
			_val.data1, _val.data2);
		
		if (write(pfd[1], &_val, sizeof(struct my_msg)) < 0)
		{
			perror("write()");
			return -1;
		}

		close(pfd[0]);
		close(pfd[1]);

		_exit(127);
	}
	else
	{
		struct my_msg _val;
		_val.data1 = 100;
		_val.data2 = 110;

		printf("[%s] data1:%d, data2:%d\n", "Parent Process",
			_val.data1, _val.data2);
		
		if(read(pfd[0], &_val, sizeof(struct my_msg)) < 0)
		{
			perror("read()");
			return -1;
		}

		printf("[%s] data1:%d, data2:%d\n", "After read from pipe",
			_val.data1, _val.data2);

		close(pfd[0]);
		close(pfd[1]);

		waitpid(pid, &status, 0);
	}

	return 0;
}