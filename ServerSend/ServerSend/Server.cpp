#include <stdlib.h>
#include <stdio.h>
#include <WinSock2.h>

#define BUFSIZE 4096

#pragma warning(disable: 4996)
#pragma comment(lib, "Ws2_32.lib")

int dataReceive(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0)
	{
		received = recv(s, ptr, left, flags);

		if (received == 0)
			break;
		
		left -= received;
		ptr += received;
	}

	return (len - left);
}

int main() 
{
	int retval;

	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);

	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN servaddr;
	ZeroMemory(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(listen_sock, (SOCKADDR*)&servaddr, sizeof(servaddr));

	listen(listen_sock, SOMAXCONN);

	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE];

	while (1)
	{
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);

		printf("클라이언트 접속 : IP = %s, Port = %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		char filename[256];
		ZeroMemory(filename, 256);
		dataReceive(client_sock, filename, 256,0);

		printf("받을 파일 이름 : %s", filename);

		int totalbytes;
		dataReceive(client_sock, (char*)&totalbytes, sizeof(totalbytes), 0);

		printf("받을 파일 크기: %d 바이트 \n",totalbytes );

		FILE *fp = fopen(filename, "wb");

		int numtotal = 0;

		while (1)
		{
			retval = dataReceive(client_sock, buf, BUFSIZE, 0);

			if (retval == 0)
			{
				break;
			}
			else {
				fwrite(buf,	1, retval, fp);

				numtotal += retval;
			}
		}

		fclose(fp);

		if (numtotal == totalbytes)
			printf("파일을 성공적으로 받았습니다.\n");
		else
			printf("파일을 제대로 받지 못했습니다.\n");

		closesocket(client_sock);
		printf("클라이언트 종료 : IP = %s, Port = %d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
	}

	closesocket(listen_sock);

	WSACleanup();
	return 0;

}