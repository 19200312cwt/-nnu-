#include"fifo_h.h"


int main(int argc,char* argv[])
{
	int fd;
	struct fifo_cmd cmd;
	if((fd=open(FIFO_PATH,O_WRONLY))<0)
	{
		perror("open fail") ;
		exit(-1);
	}
	cmd.pid=getpid();
	while(1)
	{
		printf("please enter a command string");
		fgets(cmd.cmd,sizeof(cmd.cmd),stdin);
		cmd.cmd[strlen(cmd.cmd)-1]=0;
		if(write(fd,&cmd,sizeof(cmd))<0)
		{
			perror("write fail");
			exit(-1);
		}
	}
	return 0;
 }

