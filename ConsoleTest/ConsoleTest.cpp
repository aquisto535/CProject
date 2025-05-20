// EventLogClient.cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <time.h> 
#pragma comment(lib, "ws2_32.lib")

#define MAX_BUFFER 4096
#define DEFAULT_PORT 9000

typedef struct _EVENT_LOG_PACKET {
    DWORD dwSize;           // 전체 패킷 크기
    DWORD dwEventLogType;   // 이벤트 로그 타입 (시스템, 애플리케이션 등)
    DWORD dwEventCount;     // 전송할 이벤트 개수
    BYTE byData[1];         // 가변 길이 데이터 시작 위치
} EVENT_LOG_PACKET, * PEVENT_LOG_PACKET;

// 이벤트 로그 레코드 출력 함수
void DisplayEventLogRecord(EVENTLOGRECORD* pelr) {
    LPWSTR lpSourceName = (LPWSTR)((LPBYTE)pelr + sizeof(EVENTLOGRECORD));
    LPWSTR lpComputerName = lpSourceName + wcslen(lpSourceName) + 1;

    wprintf(L"이벤트 ID: %d\n", pelr->EventID);
    wprintf(L"이벤트 소스: %s\n", lpSourceName);
    wprintf(L"컴퓨터 이름: %s\n", lpComputerName);

    wchar_t* timeStr = _wctime32((__time32_t*)&pelr->TimeGenerated);
    if (timeStr != nullptr) {
        // 개행 문자 제거
        size_t len = wcslen(timeStr);
        if (len > 0 && timeStr[len - 1] == L'\n') {
            timeStr[len - 1] = L'\0';
        }
        wprintf(L"시간: %s\n", timeStr);
    }
    else {
        wprintf(L"시간: 알 수 없음\n");
    }
    
    switch (pelr->EventType) {
    case EVENTLOG_ERROR_TYPE:
        wprintf(L"유형: 오류\n");
        break;
    case EVENTLOG_WARNING_TYPE:
        wprintf(L"유형: 경고\n");
        break;
    case EVENTLOG_INFORMATION_TYPE:
        wprintf(L"유형: 정보\n");
        break;
    default:
        wprintf(L"유형: 기타(%d)\n", pelr->EventType);
    }

    wprintf(L"---------------------------------------\n");
}

// 이벤트 로그 패킷 처리 함수
void ProcessEventLogPacket(PEVENT_LOG_PACKET pPacket) {
    EVENTLOGRECORD* pelr = NULL;
    DWORD dwBytesToRead = 0;
    DWORD dwMinimumBytesToRead = 0;
    DWORD dwRead = 0;

    printf("이벤트 로그 패킷 수신 (크기: %d 바이트, 이벤트 수: %d)\n",
        pPacket->dwSize, pPacket->dwEventCount);
    printf("---------------------------------------\n");

    dwBytesToRead = pPacket->dwSize - (sizeof(EVENT_LOG_PACKET) - sizeof(BYTE));
    pelr = (EVENTLOGRECORD*)pPacket->byData;

    // 패킷에서 이벤트 레코드 순회
    while (dwRead < dwBytesToRead) {
        // 최소 레코드 크기 확인
        dwMinimumBytesToRead = sizeof(EVENTLOGRECORD);
        if ((dwBytesToRead - dwRead) < dwMinimumBytesToRead) {
            printf("잘못된 이벤트 레코드 형식\n");
            break;
        }

        // 이벤트 레코드 출력
        DisplayEventLogRecord(pelr);

        // 다음 레코드로 이동
        dwRead += pelr->Length;
        pelr = (EVENTLOGRECORD*)((LPBYTE)pelr + pelr->Length);

        // 모든 이벤트를 읽었는지 확인
        if (dwRead >= dwBytesToRead) {
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN servAddr;
    char szBuffer[MAX_BUFFER];
    const char* pszServerIP = "192.168.111.129"; // 기본값: 로컬호스트
    int iPortNum = DEFAULT_PORT;
    PEVENT_LOG_PACKET pPacket = NULL;
    int iPacketSize = 0;

    // 명령행 인수 처리
    if (argc > 1) {
        pszServerIP = argv[1];
    }

    if (argc > 2) {
        iPortNum = atoi(argv[2]);
    }

    // Winsock 초기화
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup() 실패\n");
        return 1;
    }

    // 소켓 생성
    hSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (hSocket == INVALID_SOCKET) {
        printf("소켓 생성 실패\n");
        WSACleanup();
        return 1;
    }

    // 서버 주소 설정
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(pszServerIP);
    servAddr.sin_port = htons(iPortNum);

    // 서버에 연결
    if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
        printf("서버 연결 실패\n");
        closesocket(hSocket);
        WSACleanup();
        return 1;
    }

    printf("서버에 연결되었습니다. (%s:%d)\n", pszServerIP, iPortNum);

    // 시스템 이벤트 로그 요청
    strcpy(szBuffer, "GET_SYSTEM_LOGS");
    send(hSocket, szBuffer, (int)strlen(szBuffer) + 1, 0);

    // 응답 수신
    iPacketSize = recv(hSocket, szBuffer, MAX_BUFFER, 0);
    if (iPacketSize <= 0) {
        printf("서버로부터 응답을 받지 못했습니다.\n");
    }
    else {
        // 수신된 데이터가 패킷 형식인지 확인
        pPacket = (PEVENT_LOG_PACKET)szBuffer;
        if (pPacket->dwSize >= sizeof(EVENT_LOG_PACKET) && pPacket->dwSize == (DWORD)iPacketSize) {
            // 이벤트 로그 패킷 처리
            ProcessEventLogPacket(pPacket);
        }
        else {
            // 오류 메시지 출력
            printf("서버 응답: %s\n", szBuffer);
        }
    }

    closesocket(hSocket);
    WSACleanup();

    system("pause");

    return 0;
}