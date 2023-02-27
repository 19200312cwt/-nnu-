#include<stdio.h> 
#include<signal.h>
#include<unistd.h>

void ouch(int sig)
{
	printf("OUCH I got a signal");
}

int main()
{
	struct sigaction act;
	act.sa_handler=ouch;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	sigaction(SIGINT,&act,NULL);
	while(1)
	{
		printf("hello world\n");
		sleep(1);
	}
	return 0;
 }

