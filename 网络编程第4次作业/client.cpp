#include <stdio.h>
#include <WinSock2.h>
#pragma comment ( lib,"WS2_32.lib" )  
#pragma warning(disable : 4996)
#define RECEIVER_ADDRESS "127.0.0.1"
#define PORT 8000

int main()
{
	WSAData wasData;
	SOCKET sendSocket;
	SOCKADDR_IN receiverAddr;
	int addrLength = 0;
	char sendBuf[1024] = "fengqiangguo";
	int sendBufLength = 1024;
	int ret = 0;

	// 初始化
	WSAStartup(MAKEWORD(2, 2), &wasData);

	// 创建套接字
	// 套接字类型—：UDP/IP-SOCK_DGRAM
	// 协议：UDP-IPPROTO_UDP
	sendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SOCKET_ERROR == sendSocket) {
		printf("Create Socket Error!");
		goto exit;
	}

	// 创建一个SOCKADDR_IN结构，指定接收端地址信息
	receiverAddr.sin_family = AF_INET;   // 使用IP地址族
	receiverAddr.sin_port = htons(PORT); // 端口号
	receiverAddr.sin_addr.S_un.S_addr = inet_addr(RECEIVER_ADDRESS);

	while (1) { 
		if (scanf("%s",sendBuf)) {
			ret = sendto(sendSocket, sendBuf, sizeof(sendBuf), 0, (SOCKADDR*)&receiverAddr, sizeof(receiverAddr));
			if (0 == ret) {
				printf("fail to send\n");
			}
			printf("send info: %s\n", sendBuf);
			memset(sendBuf, 0, sizeof(sendBuf));
		}
	}

exit:
	closesocket(sendSocket);
	system("pause");
	return 0;
}
