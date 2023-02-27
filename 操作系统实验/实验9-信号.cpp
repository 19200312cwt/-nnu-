#include<signal.h> 
#include<stdio.h>
#include<unistd.h>



void ouch(int sig)
{
	printf("OUCH!-L GOT SIGNAL %d\n",sig);
	signal(SIGINT,SIG_DFL);
}

int main()
{
	signal(SIGINT,ouch);
	while(1) 
	{
		printf("hello,world\n");
		sleep(1);
	}

	return 0;
 }

