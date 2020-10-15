#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <string.h>

#define MSGQKEY	51234

struct msgbuf{
	long mtype;
	char mtext[BUFSIZ];
};

int main()
{
	key_t key = MSGQKEY;
	int mqid; /* msgget */
	struct msgbuf* mb;
	int ret;

	char* _text = "Embedded System!";
	mb = (struct msgbuf*) malloc(sizeof(struct msgbuf) + strlen(_text));

	/* msgq channel create*/
	if ((mqid = msgget(key, 0666)) < 0)
	{
		perror("msgget()");
		return -1;
	}

	mb->mtype = 1;
	strcpy(mb->mtext, _text);
	ret = msgsnd(mqid, mb, strlen(_text)+1, 0);
	if(ret < 0)
	{
		perror("msgsnd()");
		return -1;
	}

	#if 1
	mb->mtype = 2;
	memset(mb->mtext, 0, sizeof(mb->mtext));
	ret = msgsnd(mqid, mb, sizeof(mb->mtext), 0);
	if(ret < 0)
	{
		perror("msgsnd()");
		return -1;
	}
	#endif

	return 0;
}