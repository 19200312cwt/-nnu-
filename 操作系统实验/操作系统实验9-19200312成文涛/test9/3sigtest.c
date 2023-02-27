#include<signal.h> 
#include<stdio.h>
#include<unistd.h>



void ouch(int sig)
{
	switch(sig)
	{
		case 1:{printf("get signal SIGHUP");break;}
		case 2:{printf("get signal SIGINT");break;}
		case 3:{printf("get signal SIGQUIT");break;}
	}
//	printf("OUCH GOT SIGNAL %d\n",sig);
//	signal(SIGINT,SIG_DFL);
}

int main()
{
	signal(SIGHUP,ouch);
	signal(SIGINT,ouch);
	signal(SIGQUIT,ouch);
	while(1) 
	{
		printf("hello,world\n");
		sleep(1);
	}

	return 0;
 }

