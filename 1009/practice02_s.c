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
	_val.data1 = 1;
	_val.data2 = 2;

	/* Server: if channel exist, unlink the channel */
	unlink(FIFOFILE);

	if(mkfifo(FIFOFILE, 0666) < 0)
	{
		perror("mkfifo()");
		return -1;
	}

	if((fd = open(FIFOFILE, O_WRONLY)) < 0)
	{
		perror("open()");
		return -1;
	}

	printf("%s\n", "Channel Established");

	while(1)
	{
		write(fd, &_val, sizeof(struct my_msg));
		_val.data1++;
		_val.data2++;
		
		sleep(1);
	}

	close(fd);
	return 0;
}