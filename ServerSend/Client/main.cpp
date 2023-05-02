#include <stdlib.h>
#include <stdio.h>
#include <WinSock2.h>

#define BUFSIZE 4096

#pragma warning(disable: 4996)
#pragma comment(lib, "Ws2_32.lib")

int main()
{
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2,2), &wsa) !=0)
	{
		return -1;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9000);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	char myFile[256] = "sample.mp4";

	connect(sock, (SOCKADDR*)&servaddr, sizeof(servaddr));
	printf("������ ���� ���� : IP = %s, Port = %d\n", inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port));

	FILE* fp = fopen(myFile, "rb");

	char filename[256];
	ZeroMemory(filename, 256);
	sprintf(filename, myFile);

	send(sock, filename, 256,0);

	fseek(fp, 0, SEEK_END);
	int totalbytes = ftell(fp);

	// ������ ũ�⸦ ���� ����
	send(sock, (char*)&totalbytes, sizeof(totalbytes), 0 );

	char buf[BUFSIZE];
	int numread;
	int numtotal = 0;

	//���� �����͸� ������ �������� �̵��� ���� �����͸� �е��� ����
	rewind(fp);

	while (1)
	{
		numread = fread(buf, 1, BUFSIZE, fp);

		if (numread > 0)
		{
			send(sock, buf, numread, 0);
			numtotal += numread;
		}
		else if (numread == 0 && numtotal == totalbytes)
		{
			printf("�� %d ����Ʈ ���� ������ �Ϸ��߽��ϴ�\n", numtotal);
			break;
		}
	}

	fclose(fp);
	closesocket(sock);
	printf("������ ���� ���� : IP = %s, Port = %d\n", inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port) );

	WSACleanup();
	return 0;
}