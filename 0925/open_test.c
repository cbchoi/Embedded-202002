#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//int open(const char *pathname, int oflag, … /*, mode_t  mode */);

int main()
{
	char buf[100];
	int fd = 0;
	size_t ret = 0;
	fd = open("./open_test.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR|S_IRGRP);	

	write(fd, "47987", strlen("47987"));
	close(fd); 

	fd = open("./open_test.txt", O_RDONLY);	

	ret = read(fd, buf, 100);
	buf[ret] = '\0';
	printf("%ld, %s\n", ret, buf);
	close(fd); 
	
	return 0;
}