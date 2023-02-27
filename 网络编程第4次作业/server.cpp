#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#pragma comment ( lib,"WS2_32.lib" )  

#define RECEIVER_ADDRESS "127.0.0.1"
#define PORT 8000
#pragma warning(disable : 4996)
void transAddrToBuf(SOCKADDR_IN sockAddr, char* buffer)
{
	if (!buffer) {
		return;
	}
	sprintf(buffer, "%s:%d", inet_ntoa(sockAddr.sin_addr), ntohs(sockAddr.sin_port));
}

int main()
{
	WSAData wasData;
	SOCKET recvSocket;
	SOCKADDR_IN receiverAddr;
	char recvBuf[1024] = { 0 };
	int recvBufLength = 1024;

	SOCKADDR_IN senderAddr;
	memset(&senderAddr, 0, sizeof(senderAddr));
	int senderAddrLength = sizeof(senderAddr);
	char senderInfo[30] = { 0 };

	int ret = -1;

	// 初始化
	WSAStartup(MAKEWORD(2, 2), &wasData);

	// 创建套接字
	// 套接字类型—：UDP/IP-SOCK_DGRAM
	// 协议：UDP-IPPROTO_UDP
	recvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SOCKET_ERROR == recvSocket) {
		printf("Create Socket Error!");
		goto exit;
	}

	// 创建一个SOCKADDR_IN结构，指定接收端地址信息
	receiverAddr.sin_family = AF_INET;   // 使用IP地址族
	receiverAddr.sin_port = htons(PORT); // 端口号
	receiverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	// bind将地址信息和套接字关联
	ret = bind(recvSocket, (SOCKADDR*)&receiverAddr, sizeof(receiverAddr));
	if (0 != ret) {
		printf("bind error with ErrorNum %d\n", WSAGetLastError());
		goto exit;
	}

	// 接收数据报
	while (1) {
		ret = recvfrom(recvSocket, recvBuf, recvBufLength, 0, (SOCKADDR*)&senderAddr, &senderAddrLength);
		if (ret > 0) {
			printf("recv info：");
			transAddrToBuf(senderAddr, senderInfo);
			//printf("%s\n", senderInfo);
			printf("%s\n", recvBuf);
		}
	}

exit:
	closesocket(recvSocket);
	system("pause");
	return 0;
}