#include "winsock2.h"
#include "stdio.h"
#include<io.h>
#include<fcntl.h>

void _ERROR(char * s)
{
  printf("%s出错！错误代码：%d\n",s,WSAGetLastError());
}

void dir(SOCKET sd)
{
	char path[50];
	printf("查看目录路径：");
	gets_s(path);
	path[strlen(path)] = 0;

	send(sd, path, strlen(path), 0);

	char dir1[2048];
	int num = recv(sd, dir1, 1024, 0);
	dir1[num] = 0;

	printf("目录：\n%s", dir1);
}

void Get(int sd)
{
	char fname[50];
	char data[1024];	
	printf("文件路径:");
	gets_s(fname);
	fname[strlen(fname)] = 0;
	send(sd, fname, strlen(fname), 0);
	printf("发送完成！");
	int num = recv(sd, data, 1024, 0);
	data[num] = 0;

	printf("%d\n", num);

	char fname1[30];
	printf("下载至路径：");
	gets_s(fname1);

	int f1 = open(fname1, O_CREAT | O_WRONLY);

	int num1 = write(f1, data, num);
	printf("完成！%d", num1);
}

void Put(int sd)
{
	char data[1024];
	char fname1[50];
	printf("请输入目标路径：");
	gets_s(fname1);
	fname1[strlen(fname1)] = '\0';
	send(sd, fname1, strlen(fname1), 0);
	printf("上传文件路径：");
	char fname2[50];
	gets_s(fname2);
	int fn = open(fname2, O_CREAT | O_RDONLY);
	
	int num1 = read(fn, data, 1024);
	data[num1] = '\0';
	send(sd, data, strlen(data), 0);
	printf("完成！");
}

	void main(void)
	{
	 WSADATA wsaData;
	 if (WSAStartup(0x0202,&wsaData)!=0)
	 {
		 _ERROR("WSAStartup()");
		 exit(-1);
	 }

	 SOCKET sd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	 if (sd==INVALID_SOCKET)
	 {
		 _ERROR("socket()");
		 WSACleanup();
		 exit(-1);
	 }
	 struct sockaddr_in saddr;
	 memset(&saddr,0,sizeof(saddr));
	 saddr.sin_family=AF_INET;
	 saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	 saddr.sin_port=htons(9999);

	 printf("向服务器：127.0.0.1 端口号：9999 发起连接...");
	 if (connect(sd,(struct sockaddr * )&saddr,sizeof(saddr))==SOCKET_ERROR)
	 {
		 _ERROR("connect()");
		 closesocket(sd);
		 WSACleanup();
		 exit(-1);
	 }

	 printf("已连接成功！\n");

	 char menu[50];
	 int num1 = recv(sd, menu, 50, 0);
	 menu[num1] = 0;
	 printf("服务器信息：\n%s", menu);

		 char flag[20];
		 while (1)
		 {
			 printf("\n请输入选项：");
			 gets_s(flag);
			 send(sd, flag, 20, 0);
			 if (strcmp(flag, "1") == 0)
				 dir(sd);
			 else if (strcmp(flag, "2") == 0)
				 Get(sd);
			 else if (strcmp(flag, "3") == 0)
				 Put(sd);
			 else
				 break;
		 }
 
		closesocket(sd);
		WSACleanup();
	}

