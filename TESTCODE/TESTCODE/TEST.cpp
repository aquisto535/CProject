// ===== 파일 맨 위 (주석도 없음!) =====
#define INITGUID                 // ← 이것이 핵심!
#include <initguid.h>        // ← GUID 실제 정의
#include <windows.h>
#include <objbase.h>         // ← CoCreateInstance용
#include <oleacc.h>          // ← 마지막!

#pragma comment(lib, "oleacc.lib")
#pragma comment(lib, "uuid.lib")

// 테스트 코드
int main() {
    IAccPropServices* p = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_AccPropServices, nullptr, CLSCTX_INPROC_SERVER,
        IID_IAccPropServices, (void**)&p);
    return SUCCEEDED(hr) ? 0 : 1;
}
