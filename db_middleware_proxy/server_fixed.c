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

static void rollback_if_needed(PGconn* conn) {
    if (PQtransactionStatus(conn) == PQTRANS_INERROR) {
        PQexec(conn, "ROLLBACK");
        printf("[SERVER] ROLLBACK executed\n");
    }
}

static int exec_ok(PGresult* res) {
    ExecStatusType s = PQresultStatus(res);
    return (s == PGRES_COMMAND_OK || s == PGRES_TUPLES_OK);
}

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
    PGresult* res = NULL;
    char sql[256] = {0,};

    printf("\n[SERVER] handle_request(key=%s)\n", key);

    /* 트랜잭션 시작 */
    res = PQexec(conn_main, "BEGIN");
    if (!exec_ok(res)) {
        printf("[SERVER] BEGIN failed\n");
        PQclear(res);
        rollback_if_needed(conn_main);
        return;
    }
    PQclear(res);

    /* INSERT */
    snprintf(sql, sizeof(sql),
        "INSERT INTO test_data(key,value) VALUES('%s','v')",
        key);

    printf("Query : %s", sql);

    res = PQexec(conn_main, sql);

    if (!exec_ok(res)) {
        printf("[SERVER] INSERT failed: %s",
            PQerrorMessage(conn_main));
        PQclear(res);
        rollback_if_needed(conn_main);

        /* 요청에 대한 명확한 응답 */
        printf("[SERVER] SEND ERROR RESPONSE (INSERT)\n");
        return;
    }
    PQclear(res);

    /* SELECT */
    res = PQexec(conn_main,
        "SELECT value FROM test_data WHERE key='A'");

    printf("Query : SELECT value FROM test_data WHERE key='A'");

    if (!exec_ok(res)) {
        printf("[SERVER] SELECT failed: %s",
            PQerrorMessage(conn_main));
        PQclear(res);
        rollback_if_needed(conn_main);

        printf("[SERVER] SEND ERROR RESPONSE (SELECT)\n");
        return;
    }

    /* 결과 0행도 정상 응답 - 트랜잭션 확실히 정리!*/ 
    if (PQntuples(res) == 0) {
        printf("[SERVER] SEND NOT FOUND RESPONSE\n");
        PQclear(res);
        PQexec(conn_main, "COMMIT");
        return;
    }

    printf("[SERVER] SEND RESPONSE: %s\n",
        PQgetvalue(res, 0, 0));

    PQclear(res);

    /* COMMIT */
    res = PQexec(conn_main, "COMMIT");
    if (!exec_ok(res)) {
        printf("[SERVER] COMMIT failed\n");
        PQclear(res);
        rollback_if_needed(conn_main);
        return;
    }
    PQclear(res);
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
    char szDBConn[256] = { 0 };
    sprintf_s(szDBConn, 75, "%s=%s %s=%s %s=%s %s=%s %s=%s",
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
    handle_request("P");   

    printf("\n[SERVER] test finished\n");
    Sleep(5);
    return 0;
}
