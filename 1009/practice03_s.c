#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>

#define MSGQKEY	51234

struct msgbuf{
	long mtype;
	char mtext[BUFSIZ];
};

int main()
{
	key_t key = MSGQKEY;
	int n; /* msgrcv */
	int mqid; /* msgget */
	struct msgbuf mb;

	/* msgq channel create*/
	if ((mqid = msgget(key, IPC_CREAT|IPC_EXCL| 0666)) < 0)
	{
		perror("msgget()");
		return -1;
	}

	while((n = msgrcv(mqid, &mb, sizeof(struct msgbuf), 0, 0)) > 0)
	{
		switch(mb.mtype)
		{
		case 1:
			{/* mtype == 0 print */
				write(STDOUT_FILENO, mb.mtext, n);
			}
			break;
		case 2:
			{/* mtype == 1 remove channel */	
				if(msgctl(mqid, IPC_RMID, (struct msqid_ds *) 0) < 0)
				{
					perror("msgctl()");
					return -1;
				}
			}
			break;
		}
	}
	
	return 0;
}