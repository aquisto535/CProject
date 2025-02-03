#include <windows.h>
#include <winldap.h>
#include <iostream>

#pragma comment(lib, "wldap32.lib")  // LDAP 라이브러리

int main() {
    LDAP* ld;
    ULONG version = LDAP_VERSION3;
    ULONG result;

    // 1️⃣ LDAP 연결 (포트 389 사용)
    ld = ldap_init(L"ldap.mydomain.com", LDAP_PORT);
    if (ld == NULL) {
        std::cerr << "Failed to initialize LDAP connection." << std::endl;
        return 1;
    }

    // 2️⃣ LDAP 버전 설정
    ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version);

    // 3️⃣ STARTTLS 요청
    result = ldap_start_tls_s(ld, NULL, NULL);
    if (result != LDAP_SUCCESS) {
        std::cerr << "STARTTLS failed: " << ldap_err2string(result) << std::endl;
        ldap_unbind(ld);
        return 1;
    }

    std::cout << "STARTTLS negotiation successful!" << std::endl;

    // 4️⃣ 인증 (Simple Bind 사용 예시)
    result = ldap_simple_bind_s(ld, L"CN=User,DC=mydomain,DC=com", L"password123");
    if (result != LDAP_SUCCESS) {
        std::cerr << "LDAP bind failed: " << ldap_err2string(result) << std::endl;
        ldap_unbind(ld);
        return 1;
    }

    std::cout << "LDAP authentication successful!" << std::endl;

    // 5️⃣ 연결 종료
    ldap_unbind(ld);
    return 0;
}
