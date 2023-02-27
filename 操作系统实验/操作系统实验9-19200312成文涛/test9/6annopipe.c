#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<wait.h> 
#define MAX_LINE 180

int main()
{
	int thepipe[2],ret;
	char buf[MAX_LINE+1];
	const char* testbuf="a test string";
	if(pipe(thepipe)==0)
	{
		if(fork()==0)
		{
			ret=read(thepipe[0],buf,MAX_LINE);
			buf[ret]=0;
			printf("Child read %s\n",buf);
		}
		else
		{
			sleep(5);
			ret=write(thepipe[1],testbuf,strlen(testbuf));
			ret=wait(NULL); 
		}
		close(thepipe[0]);
		close(thepipe[1]);
	}
	return 0;
 }

