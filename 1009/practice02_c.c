#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFOFILE "fifo"

struct my_msg
{
	int data1;
	int data2;
};

int main()
{
	int fd;
	struct my_msg _val;

	int flag = 0;

	while(1)
	{
		if(!flag)
		{
			if((fd = open(FIFOFILE, O_RDONLY)) < 0)
			{
				perror("open()");
			}
			else
				flag = 1;
		}
		else
		{
			read(fd, &_val, sizeof(struct my_msg));

			printf("[%s] data1:%d, data2:%d\n", "Client Process",
					_val.data1, _val.data2);
		}
		sleep(1);
	}

	close(fd);
	return 0;
}