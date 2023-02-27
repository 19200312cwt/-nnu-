#pragma warning(disable : 4996)
#include "winsock2.h"
#include<stdlib.h>
#include <stdio.h>
#include<io.h>
#include<fcntl.h>

void _ERROR(char * s)
{
  printf("%s 出错！出错代码：%d \n",s,WSAGetLastError());
}

void dir(SOCKET clisd)
{
	char result[2048] = { 0 };
	char path[50];
	char order[50] = { 0 };
	int num = recv(clisd, path, 50, 0);
	path[num] = 0;
	printf("客户端输入路径：%s\n", path);

	strcat(order, "dir ");
	strcat(order, path);
	FILE* pipe = _popen(order, "r");
	if (!pipe) {
		strcat(result, "Err");
	}
	else {
		strcat(result, "OK\n");
		char buf[2048] = { 0 };
		while (fgets(buf, 2048, pipe)) {
			strcat(result, buf);
		}
		fclose(pipe);
	}

	printf("目录：%s\n", result);
	send(clisd, result, strlen(result), 0);
	printf("目录已发送至客户端");
}

void Get(SOCKET clisd)
{
	char fname[254];
	int fnum = recv(clisd, fname, 254, 0);
	if (fnum == SOCKET_ERROR)
	{
		_ERROR("recv()");
		closesocket(clisd);
		
		WSACleanup();
		exit(-1);
	}
	fname[fnum] = 0;
	printf("客户机输入文件名：%s \n", fname);

	int f = open(fname, O_CREAT | O_RDONLY);
	
	char data1[1024];
	int num = read(f, data1, 1024);
	data1[num] = 0;

	printf("%s \n", data1);
	send(clisd, data1, strlen(data1), 0);
	printf("已发送至客户端");
}

void Put(int clisd)
{
	char fname[254];
	//getFiname(clisd, fname, 254);
	int fnum = recv(clisd, fname, 254, 0);
	if (fnum == SOCKET_ERROR)
	{
		_ERROR("recv()");
		closesocket(clisd);
		//		closesocket(lsd);
		WSACleanup();
		exit(-1);
	}
	fname[fnum] = 0;
	printf("客户机输入文件名：%s \n", fname);

	int f = open(fname, O_CREAT | O_WRONLY);
	
	char data1[1024];
	int num1 = recv(clisd, data1, 1024, 0);
	data1[num1] = '\0';
	int num = write(f, data1, strlen(data1));
	printf("已成功上传");
}

void main(void)
{
	 WSADATA wsaData;
	 if (WSAStartup(0x0202,&wsaData)!=0)
	 {
	   _ERROR("WSAStartup()");
	   exit(-1);
	 }	

	 SOCKET lsd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	 if (lsd==INVALID_SOCKET)
	 {
		 _ERROR("socket()");
		 WSACleanup();
		 exit(-1);
	 }

 //server IP:127.0.0.1  port : 9999

	 struct sockaddr_in server;
	 memset(&server,0,sizeof(server));
	 server.sin_family=AF_INET;
	 server.sin_port=htons(9999);
	 server.sin_addr.s_addr = inet_addr("127.0.0.1");
	 if (bind(lsd,(struct sockaddr *)&server,sizeof(server))==SOCKET_ERROR)
	 {
		 _ERROR("bind()");
		 closesocket(lsd);
		 WSACleanup();
		 exit(-1);
	 }

	if (listen(lsd,5)==SOCKET_ERROR)
	{
		 _ERROR("listen()");
		 closesocket(lsd);
		 WSACleanup();
		 exit(-1);
	}

	printf("TCP服务器程序在端口号：9999上等待连接......\n");
	struct sockaddr_in caddr;
	int len = sizeof(caddr);
	SOCKET clisd = accept(lsd,(struct sockaddr *)&caddr,&len);
	if ( clisd == INVALID_SOCKET )
	{
		 _ERROR("accept()");
		 closesocket(lsd);
		 WSACleanup();
		 exit(-1);
	}

	printf("客户机IP：%s 端口号：%d 已连接进来！\n",inet_ntoa( caddr.sin_addr),ntohs(caddr.sin_port));

	char flag[20];
	char menu[] = "menu list:\n1.dir\n2.get\n3.put\n4.quit \0";

	send(clisd, menu, strlen(menu), 0);
	do {
		int num1 = recv(clisd, flag, 20, 0);
		if (strcmp(flag, "1") == 0)
		{
			dir(clisd);
		}
		else if (strcmp(flag, "2") == 0)
			Get(clisd);
		else if (strcmp(flag, "3") == 0)
			Put(clisd);
		else
			break;
	} while (1);

	printf("谢谢，再见！");
	closesocket(clisd);
	closesocket(lsd);
	WSACleanup();

	}//main

