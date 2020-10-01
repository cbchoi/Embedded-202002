#include <stdio.h>
#include <string.h>

#include <definitions.h>


int main()
{
	printf("%s\n", "Test Suite01 >> Move path and list file");
	{
		/* Test Setup */
		char prev_cwd[_MAX_PATH];
		strcpy(prev_cwd, get_cwd());
		printf("%s\n", prev_cwd);
		
		/* Change current working directory to parent Directory */
		move_to_parent();
		move_to_parent();
		
		/* listup files */
		print_files(".");

		/* Teardown */
		move_to_given_path(prev_cwd);
		strcpy(prev_cwd, get_cwd());
		printf("%s\n", prev_cwd);
	}

	printf("\n%s\n", "Test Suite02 >> Create directory and list files");
	{
		create_directory("test");
		print_files(".");
	} 

	printf("\n%s\n", "Test Suite03 >> Create File & Read Contents");
	{
		create_file("./test/id.bin", "47987");
		peek_file("./test/id.bin");
	}

	printf("\n%s\n", "Test Suite04 >> Copy Large File");
	{
		copy_large_files("../../data/large_file.bin", "./test/large_file.bin", 80);
	}

	printf("\n%s\n", "Test Suite05 >> Find letters in some position");
	{
		#define CODE_LEN 2
		int candidate[] = {22701, 24609, 24883, 23147, 25114, 23028, 20663, 24221};
		int count = sizeof(candidate)/sizeof(int);
		int i;
		char* recon_buff = malloc( sizeof(char) * count *  CODE_LEN) + 1;
		
		for(i = 0; i < count; i++)
		{
			read_file("./test/large_file.bin", recon_buff+(i * CODE_LEN), CODE_LEN, candidate[i]);
		}
		recon_buff[sizeof(char) * count *  CODE_LEN] = '\0';
		printf("Reconstructed Code: %s\n", recon_buff);
	}

	printf("\n%s\n", "Test Suite06 >> Find letters in some position");
	{
		size_t file_size = 0;
		printf("File Info using lstat\n");
		print_file_size_with_stat("./test/large_file.bin");

		file_size = get_file_size("./test/large_file.bin");		
		printf("File size using lseek: %ld bytes\n", file_size);
		
	}

	return 0;
	
}