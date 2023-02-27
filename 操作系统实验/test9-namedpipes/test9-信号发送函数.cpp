#include<stdio.h>
#include<signal.h> 
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>



static int alarm_fired=0;
void ding(int sig)
{
	alarm_fired=1;
}
int main()
{
	pid_t pid;
	printf("alarm application starting\n");
	pid=fork();
	switch(pid)
	{
		case -1:
			perror("fork failed");
			exit(1);
		case 0:
			sleep(5) ;
			kill(getppid(),SIGALRM);
			exit(0);
	}
		printf("waiting for alarm to do off\n");
		signal(SIGALRM,ding);
		pause();
		if(alarm_fired)
			printf("Ding!\n1;")
		printf("done");
		
	return 0;
 }

