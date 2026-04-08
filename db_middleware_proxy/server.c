#ifdef _WIN32
#include <windows.h>
#include <process.h>   // _beginthreadex
#else
#include <pthread.h>
#endif

#include <libpq-fe.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
unsigned __stdcall worker_thread(void* arg)
#else
void* worker_thread(void* arg)
#endif
{
    PGconn* conn = (PGconn*)arg;

    while (1) {
        PGresult* res = PQexec(conn, "SELECT * FROM watched_table");
        PQclear(res);
        Sleep(1000);
    }

    return 0;
}

PGconn* conn_main;

void handle_request(const char* key) 
{
    PGresult* res;
    char sql[256];

    PQexec(conn_main, "BEGIN");

    snprintf(sql, sizeof(sql),
        "INSERT INTO test_data(key,value) VALUES('%s','v')",
        key);

    printf("Query : %s;\n", sql);

    res = PQexec(conn_main, sql);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) 
    {
        printf("%s : DB connect failed\n", PQerrorMessage(conn_main));
        printf("[SERVER] INSERT failed (no rollback!)\n");
        //PQexec(conn_main, "ROLLBACK");
        PQclear(res);
        return; // ABORT 상태 유지
    }
    PQclear(res);

    res = PQexec(conn_main,
        "SELECT value FROM test_data WHERE key='A'");

    printf("Query : SELECT value FROM test_data WHERE key='A';\n");

    if (PQntuples(res) > 0) {
        printf("[SERVER] SEND: %s\n", PQgetvalue(res, 0, 0));
    }
    else {
        printf("[SERVER] NO DATA SENT\n");
    }

    PQclear(res);
    PQexec(conn_main, "COMMIT");
}

void MakeSubThread(PGconn* w1, PGconn* w2)
{
    HANDLE hThread1 = (HANDLE)_beginthreadex(NULL, 0, worker_thread, w1, 0, NULL);

    if (hThread1 == 0)
    {
        return;
        // 에러 처리
    }

    HANDLE hThread2 = (HANDLE)_beginthreadex(NULL, 0, worker_thread, w2, 0, NULL);

    if (hThread2 == 0) {
        // 에러 처리
        CloseHandle(hThread1);  // 첫 번째 스레드 정리
        return;
    }
}

int main()
{
    char szDBConn[256] = {0};
    sprintf_s(szDBConn, 75,"%s=%s %s=%s %s=%s %s=%s %s=%s",
        "dbname", "redcastle",
        "user", "rc",
        "password", "castle1`",
        "port", "5432",
        "hostaddr", "192.168.2.12");

    conn_main = PQconnectdb(szDBConn);
    if (PQstatus(conn_main) != CONNECTION_OK)
    {
        //int nResult = log_error(PQerrorMessage(conn_main));
        printf("%s : DB connect failed\n", PQerrorMessage(conn_main));
        return 1;
    }

    // Worker connections
    PGconn* w1 = PQconnectdb("dbname=test_data");
    PGconn* w2 = PQconnectdb("dbname=test_data");

    MakeSubThread(w1, w2);

    Sleep(1);

    // 테스트 시퀀스
    handle_request("A");   // duplicate → abort
    handle_request("X");   // SELECT 응답 누락 발생

    Sleep(5);
    return 0;
}
