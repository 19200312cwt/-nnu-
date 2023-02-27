#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
#include<stack>
#include<queue>
#include<ctime>
#include<cstring>
#include<vector>
#include<signal.h>
#include<unistd.h>
#define ll long long
using namespace std;

void sigroutine(int sig)
{
	switch(sig)
	{
		case SIGHUP:
			printf("get a signal -SIGHUP");
			break;
		case SIGINT:
			printf("get a signal -SIGINT");
			break;
		case SIGQUIT:
			printf("get a signal -SIQUIT");
			break;
	}
	return ;
}
int main(int argc , char *argv[])
{
	printf("process id is%d \n",getpid());
	signal(SIGHUP,sigroutine);
	signal(SIGINT,sigroutine);
	signal(SIGQUIT,sigroutine);
	for(;;);
	return 0;
 }

