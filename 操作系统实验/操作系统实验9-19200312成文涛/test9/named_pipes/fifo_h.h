#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#define FIFO_PATH "/home/cwt/Os_test/named_pipes/fifo_abc"
struct fifo_cmd{
	pid_t pid;
	char cmd[100];
};
