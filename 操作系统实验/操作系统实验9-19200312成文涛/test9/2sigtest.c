#include<signal.h>
#include<stdio.h>
#include<unistd.h>

void sigtest(int sig)
{
	printf("get sig %d",sig);
		switch(sig)
		{
		case 1:printf("get a signal -SIGHUP");break;
		case 2:printf("get a signal -SIGINT");break;															        case 3:printf("get a signal -SIGQUIT");break;}
			return ;
}
int main()
{
		printf("process id is%d \n",getpid());
		signal(SIGHUP,sigtest);
		signal(SIGINT,sigtest);
		signal(SIGQUIT,sigtest);
		while(1){}
 }

