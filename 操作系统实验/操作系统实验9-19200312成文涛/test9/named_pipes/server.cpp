#include"fifo_h.h"
int main(void){
	int fd,err,n;
	struct fifo_cmd cmd;
	if((err=mkfifo(FIFO_PATH,0666))<0){
		if(err!=EEXIST){
			perror("mkfifo fail");
			exit(-1);
		}
	}
	if((fd=open(FIFO_PATH,O_RDONLY))<0){
		perror("open fail");
		exit(-1);
	}
	while(1){
		if((n=read(fd,&cmd,sizeof(cmd)))<0){
			perror("read fail");
			exit(-1);
		}
		if(n>0){
			printf("command from process %d: %s\n",cmd.pid,cmd.cmd);
		}
		sleep(1);
	}
}
