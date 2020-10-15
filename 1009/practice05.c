#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_KEY 0x12345

int main()
{
	int i;
	int status;
	key_t key = SHM_KEY;
	int pid, shmid;
	int* cVal;
	void* shmem = (void*) 0;

	if((pid = fork()) == 0)
	{
		shmid = shmget(key, 0, IPC_CREAT|0666);
		if(shmid == -1)
		{
			perror("shmget()");
			return -1;
		}

		shmem = shmat(shmid, (void*) 0, 0);

		if(shmem == (void*) -1)
		{
			perror("shmat()");
			return -1;
		}

		cVal = (int *) shmem;
		*cVal = 1;

		for(i = 0; i < 3; i++)
		{
			*cVal += 1;
			printf("Child(%d) : %d\n", i, *cVal);
			sleep(1);
		}
	}
	else
	{
		shmid = shmget(key, sizeof(int), IPC_CREAT|0666);
		if(shmid == -1)
		{
			perror("shmget()");
			return -1;
		}

		shmem = shmat(shmid, (void*) 0, 0);
		if(shmem == (void*) -1)
		{
			perror("shmat()");
			return -1;
		}

		cVal = (int *) shmem;
		sleep(5);
		printf("Parent(%d) : %d\n", getpid(), *cVal);
		waitpid(pid, &status, 0);
	}

	shmctl(shmid, IPC_RMID, 0);

	return 0;
}