#include "../../Common.h"

char* SERVERIP = (char*)"127.0.0.1";
#define SERVERPORT	9000
#define BUFSIZE		512

int main(int argc, char *argv[])
{
	int retval;

	if (argc > 1)
	{
		SERVERIP = argv[1];

		WSADATA wsa;

		if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
		{
			return 1;
		}

		SOCKET sock = socket(AF_INET, SOCK_STREAM,0);
		if (sock == INVALID_SOCKET) err_quit("socket()");

		struct sockaddr_in serveraddr;
		memset(&serveraddr, 0, sizeof(serveraddr));
		serveraddr.sin_family = AF_INET;
		inet_pton(AF_INET, SERVERIP, &serveraddr.sin_addr);
		serveraddr.sin_port = htons(SERVERPORT);
		retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
		if (retval == SOCKET_ERROR) err_quit("connect()");


	}
}