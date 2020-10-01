#ifndef _DEFINITION_H
#define _DEFINITION_H

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

#ifndef _MAX_PATH
#define _MAX_PATH 255
#endif

#ifndef _MAX_BUFF
#define _MAX_BUFF 65535
#endif

char p_wdBuf[_MAX_PATH];

/* Problem 03 */
char* get_cwd()
{
	return getcwd(p_wdBuf, _MAX_PATH);
}

char* move_to_given_path(char* pPath)
{
	/* Definition */
	char* p_retBuf;

	/* Print Current Working Directory */
	p_retBuf = getcwd(p_wdBuf, _MAX_PATH);
	printf("Before: %s\n", p_retBuf);

	/* Change current directory to parent Directory */
	if( !chdir(pPath) )
	{
		/* Print Current Working Directory */
		p_retBuf = getcwd(p_wdBuf, _MAX_PATH);
		printf("After: %s\n", p_retBuf);
	}
	else
	{
		printf("Cannot change to Parent Directory\n");
	}

	p_retBuf = getcwd(p_wdBuf, _MAX_PATH);
	return p_retBuf;	
}

/* Problem 01 */
char* move_to_parent()
{
	return move_to_given_path("..");
}

int create_directory(char* name)
{
	int ret;
	ret = mkdir(name, 0777);
	if (!ret)
	{
		char p_wdBuf[_MAX_PATH];
		char* p_retBuf;

		/* Print Current Working Directory */
		p_retBuf = getcwd(p_wdBuf, _MAX_PATH);
		printf("Before: %s\n", p_retBuf);
		printf("New Directory Created:%s/%s\n", p_retBuf, name);
	}
	else
	{
		 printf("Unable to create directory\n"); 
	}

	return ret;
}


/* Problem 02 */
void print_files(char* path)
{
	/* Print the list of the file */
	DIR           *d;
  	struct dirent *dir;
	d = opendir(path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if(dir->d_type == DT_DIR)
				printf("[Directory] %s\n", dir->d_name);
			else if(dir->d_type == DT_REG)
				printf("[REGFile] %s\n", dir->d_name);
		}

		closedir(d);
	}
}

void create_file(char* file_path, char* contents)
{
	int fd;
	fd = open(file_path, O_WRONLY|O_CREAT, S_IRUSR|S_IRGRP|S_IROTH);
	
	write(fd, contents, strlen(contents));
	write(fd, "\0", 1);

	close(fd);
}

void create_binary_file(char* file_path, char* contents)
{
	FILE* fd;
	fd = fopen(file_path, "wb");
	fwrite(contents, strlen(contents), 1, fd);	
	fclose(fd);
}

void delete_file(char* file_path)
{
	remove(file_path);
}

void peek_file(char* file_path)
{
	int fd;
	char Buff[_MAX_BUFF];
	fd = open(file_path, O_RDONLY);
	size_t sz_file = lseek(fd, 0, SEEK_END); 
	lseek(fd, 0, 0); 

	read(fd, Buff, sz_file);
	close(fd);

	printf("Sneak a Pick of a file: %s\n", file_path);
	printf("%s\n", Buff);
}

size_t get_file_size(char* file_path)
{
	int fd; 	
	size_t sz_file;
	
	fd = open(file_path, O_RDONLY);
    sz_file = lseek(fd, 0, SEEK_END); 
	
	close(fd);
	return sz_file;
}

void read_file(char* file_path, char* buff, int buf_size, int index)
{
    int fd; 

    fd = open(file_path, O_RDONLY);
    lseek(fd, index, SEEK_CUR);

    read(fd, buff, buf_size); 
    
    close(fd);
}

void copy_large_files(char* src_path, char* dst_path, int buff_size)
{
	printf("SRC PATH: %s\n", src_path);
	printf("DST PATH: %s\n", dst_path);

	int index = 0;
	char* buff = malloc(sizeof(char) * buff_size);
	size_t file_size = get_file_size(src_path);
	printf("Size of File: %ld\n", (long int) file_size);

	FILE* fd = fopen(dst_path, "w");
	fclose(fd);
	
	fd = fopen(dst_path, "a");
	
	while (index < file_size)
	{
		if(file_size - index > buff_size)
		{
			read_file(src_path, buff, buff_size, index);
			fwrite(buff, buff_size, 1, fd);
			index += buff_size;
		}
		else
		{
			read_file(src_path, buff, file_size - index, index);	
			fwrite(buff, file_size - index, 1, fd);
			index += (file_size - index);
		}
	}
	fclose(fd);
	free(buff);
}

void print_file_size_with_stat(char* file_path)
{
	struct stat sb;
	if (stat(file_path, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
	}
	printf("File size using lstat: %lld bytes\n",
        (long long) sb.st_size);
}

#endif