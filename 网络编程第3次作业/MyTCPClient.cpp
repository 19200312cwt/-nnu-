#include "winsock2.h"
#include "stdio.h"
#include<io.h>
#include<fcntl.h>

void _ERROR(char * s)
{
  printf("%s����������룺%d\n",s,WSAGetLastError());
}

void dir(SOCKET sd)
{
	char path[50];
	printf("�鿴Ŀ¼·����");
	gets_s(path);
	path[strlen(path)] = 0;

	send(sd, path, strlen(path), 0);

	char dir1[2048];
	int num = recv(sd, dir1, 1024, 0);
	dir1[num] = 0;

	printf("Ŀ¼��\n%s", dir1);
}

void Get(int sd)
{
	char fname[50];
	char data[1024];	
	printf("�ļ�·��:");
	gets_s(fname);
	fname[strlen(fname)] = 0;
	send(sd, fname, strlen(fname), 0);
	printf("������ɣ�");
	int num = recv(sd, data, 1024, 0);
	data[num] = 0;

	printf("%d\n", num);

	char fname1[30];
	printf("������·����");
	gets_s(fname1);

	int f1 = open(fname1, O_CREAT | O_WRONLY);

	int num1 = write(f1, data, num);
	printf("��ɣ�%d", num1);
}

void Put(int sd)
{
	char data[1024];
	char fname1[50];
	printf("������Ŀ��·����");
	gets_s(fname1);
	fname1[strlen(fname1)] = '\0';
	send(sd, fname1, strlen(fname1), 0);
	printf("�ϴ��ļ�·����");
	char fname2[50];
	gets_s(fname2);
	int fn = open(fname2, O_CREAT | O_RDONLY);
	
	int num1 = read(fn, data, 1024);
	data[num1] = '\0';
	send(sd, data, strlen(data), 0);
	printf("��ɣ�");
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

	 printf("���������127.0.0.1 �˿ںţ�9999 ��������...");
	 if (connect(sd,(struct sockaddr * )&saddr,sizeof(saddr))==SOCKET_ERROR)
	 {
		 _ERROR("connect()");
		 closesocket(sd);
		 WSACleanup();
		 exit(-1);
	 }

	 printf("�����ӳɹ���\n");

	 char menu[50];
	 int num1 = recv(sd, menu, 50, 0);
	 menu[num1] = 0;
	 printf("��������Ϣ��\n%s", menu);

		 char flag[20];
		 while (1)
		 {
			 printf("\n������ѡ�");
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

