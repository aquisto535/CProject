#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS // ���� C �Լ� ��� �� ��� ����
#define _WINSOCK_DEPRECATED_NO_WARNINGS // ���� ���� API ��� �� ��� ����

#include <winsock2.h> // ����2 ���� ���
#include <ws2tcpip.h> // ����2 Ȯ�� ���

#include <tchar.h> // _T(), ...
#include <stdio.h> // printf(), ...
#include <stdlib.h> // exit(), ...
#include <string.h> // strncpy(), ...

#pragma comment(lib, "ws2_32") // ws2_32.lib ��ũ

#define SERVERPORT  9000
#define BUFSIZE		512

// ���� �Լ� ���� ��� �� ����
void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	MessageBoxA(NULL, (const char*)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// ���� �Լ� ���� ���
void err_display(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[%s] %s\n", msg, (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// ���� �Լ� ���� ���
void err_display(int errcode)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[����] %s\n", (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

int main(int argc, char *argv[])
{
	int retval;

	WSADATA wsa; //������ ���Ϸ� �̷��� ����ü

	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		return 1;
	}

	// ���� ����
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("Socket()");

	// bind()
	struct sockaddr_in serveraddr; //���� �ּ� ����ü ����
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr)); // ������ ������ ���� �������� ���. ���� IP �ּҿ� ���� ��Ʈ ��ȣ�� ����
	if (retval == SOCKET_ERROR) err_quit("bind()");

	//Listen
	retval = listen(listen_sock, SOMAXCONN); //listen: TCP ���¸� LISTENING ���� ����
	if (retval == SOCKET_ERROR) err_quit("Listen()");

	//������ ��ſ� ����� ����
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	while (1)
	{	
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);//  Ŭ���̾�Ʈ�� ����ϴ� ���� ������ ���ÿ� ���� IP�� ���� ��Ʈ ��ȣ ���� 
		if (client_sock == INVALID_SOCKET)
		{
			err_display("accept()");
			break;
		}

		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP�ּ� = %s, ��Ʈ��ȣ = %d\n", addr, ntohs(clientaddr.sin_port));

		while (1)
		{
			// ù��° ����) ����� ���� ����� ����,  �ι�° ����) ���� �����͸� ������ ���ø����̼� ������ �ּ�, 
			// ����° ����) ���� ���۷κ��� ������ �ִ� �������� ũ��(buf�� ����Ű�� ������ ũ�⺸�� ũ�� �ȵ�)
			retval = recv(client_sock, buf, BUFSIZE, 0); // ������ �ޱ�
			if (retval== SOCKET_ERROR)
			{
				err_display("recv()");
				break;
			}
			else if (retval == 0 )
			{
				break;
			}

			buf[retval] = '\0';
			printf("[TCP ����] Ŭ���̾�Ʈ ����: IP�ּ�=%s, ��Ʈ��ȣ=%d\n", addr, ntohs(clientaddr.sin_port));
		
		}

		closesocket(client_sock);
		printf("[TCP ����] Ŭ���̾�Ʈ ���� : IP �ּ� : %s, ��Ʈ ��ȣ : %d\n", addr, ntohs(clientaddr.sin_port));
	}

	closesocket(listen_sock);

	WSACleanup();
	return 0;
}

