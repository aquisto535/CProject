#include <windows.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <strsafe.h>
#include "RingMemory.h"

using namespace std;

int main()
{
    CRingMemory memory;
	memory.Create(1 * 1000 * 1000); // 1 MB

    for (int i = 0; i < 10; i++)
    {
        auto* pMemoryToken = memory.Alloc(128); // unsigned char*
        if (!pMemoryToken) {
            printf("Alloc failed\n");
            continue;
        }

        // 방법 1: 문자열 리터럴을 안전하게 복사 (Visual Studio 안전 함수)
        const char* msg = "Hello, Ring!";
        //strcpy_s(reinterpret_cast<char*>(pMemoryToken), 128, msg);
        StringCbCopyA(reinterpret_cast<char*>(pMemoryToken), 128, msg);
        printf("Copied (strcpy_s): %s\n", reinterpret_cast<char*>(pMemoryToken));


        // 방법 2: std::string -> memcpy (명시적 길이 체크 + 널종료)
        std::string s = "Another message from std::string";
        size_t maxCopy = 127; // 128 바이트 중 마지막 1바이트는 '\0' 용
        size_t copyLen = min(s.size(), maxCopy);
        memcpy(pMemoryToken, s.c_str(), copyLen);
        pMemoryToken[copyLen] = 0; // 널종료
        printf("Copied (memcpy): %s\n", reinterpret_cast<char*>(pMemoryToken));
    }

    memory.Destroy();
    return 0;
}
