#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS // 구형 C 함수 사용 시 경고 끄기
#define _WINSOCK_DEPRECATED_NO_WARNINGS // 구형 소켓 API 사용 시 경고 끄기

#include <winsock2.h> // 윈속2 메인 헤더
#include <ws2tcpip.h> // 윈속2 확장 헤더

#include <tchar.h> // _T(), ...
#include <stdio.h> // printf(), ...
#include <stdlib.h> // exit(), ...
#include <string.h> // strncpy(), ...

#pragma comment(lib, "ws2_32") // ws2_32.lib 링크

#define SERVERPORT  9000
#define BUFSIZE		512

// 소켓 함수 오류 출력 후 종료
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

// 소켓 함수 오류 출력
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

// 소켓 함수 오류 출력
void err_display(int errcode)
{
	LPVOID lpMsgBuf;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(char*)&lpMsgBuf, 0, NULL);
	printf("[오류] %s\n", (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

int main(int argc, char *argv[])
{
	int retval;

	WSADATA wsa; //윈도우 소켓로 이뤄진 구조체

	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		return 1;
	}

	// 소켓 생성
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("Socket()");

	// bind()
	struct sockaddr_in serveraddr; //소켓 주소 구조체 선언
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr)); // 생성한 소켓을 서버 소켓으로 등록. 지역 IP 주소와 지역 포트 번호를 결정
	if (retval == SOCKET_ERROR) err_quit("bind()");

	//Listen
	retval = listen(listen_sock, SOMAXCONN); //listen: TCP 상태를 LISTENING 으로 변경
	if (retval == SOCKET_ERROR) err_quit("Listen()");

	//데이터 통신에 사용할 변수
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	while (1)
	{	
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr*)&clientaddr, &addrlen);//  클라이언트와 통신하는 소켓 생성과 동시에 원격 IP와 원격 포트 번호 결정 
		if (client_sock == INVALID_SOCKET)
		{
			err_display("accept()");
			break;
		}

		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP 서버] 클라이언트 접속: IP주소 = %s, 포트번호 = %d\n", addr, ntohs(clientaddr.sin_port));

		while (1)
		{
			// 첫번째 인자) 통신할 대상과 연결된 소켓,  두번째 인자) 받은 데이터를 저장할 어플리케이션 버퍼의 주소, 
			// 세번째 인자) 수신 버퍼로부터 복사할 최대 데이터의 크기(buf가 가리키는 버퍼의 크기보다 크면 안됨)
			retval = recv(client_sock, buf, BUFSIZE, 0); // 데이터 받기
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
			printf("[TCP 서버] 클라이언트 종료: IP주소=%s, 포트번호=%d\n", addr, ntohs(clientaddr.sin_port));
		
		}

		closesocket(client_sock);
		printf("[TCP 서버] 클라이언트 종료 : IP 주소 : %s, 포트 번호 : %d\n", addr, ntohs(clientaddr.sin_port));
	}

	closesocket(listen_sock);

	WSACleanup();
	return 0;
}

