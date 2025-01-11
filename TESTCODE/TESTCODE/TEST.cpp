#include <windows.h>
#include <iostream>
#include <string>

void ProcessLine(const std::string& line) {
    // ��ȣȭ�� �� ó�� ���� �߰�
    std::cout << "Processing: " << line << std::endl;
}

int main() {
    LPCWSTR filePath = L"Lorem ipsum dolor sit amet, consect.txt";

    // 1. ���� ����
    HANDLE hFile = CreateFile(
        filePath,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open file. Error: " << GetLastError() << std::endl;
        return 1;
    }

    // 2. ���� ���� ��ü ����
    HANDLE hMapping = CreateFileMapping(
        hFile,
        NULL,
        PAGE_READONLY,
        0,
        0,
        NULL);

    if (hMapping == NULL) {
        std::cerr << "Failed to create file mapping. Error: " << GetLastError() << std::endl;
        CloseHandle(hFile);
        return 1;
    }

    // 3. �޸𸮿� ����
    LPVOID pMappedFile = MapViewOfFile(
        hMapping,
        FILE_MAP_READ,
        0,
        0,
        0);

    if (pMappedFile == NULL) {
        std::cerr << "Failed to map view of file. Error: " << GetLastError() << std::endl;
        CloseHandle(hMapping);
        CloseHandle(hFile);
        return 1;
    }

    // 4. ���� ũ�� ��������
    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hFile, &fileSize)) {
        std::cerr << "Failed to get file size. Error: " << GetLastError() << std::endl;
        UnmapViewOfFile(pMappedFile);
        CloseHandle(hMapping);
        CloseHandle(hFile);
        return 1;
    }

    // 5. ������ �б�
    const char* pData = static_cast<const char*>(pMappedFile);
    std::string fileContent(pData, fileSize.QuadPart);

    // 6. �� �پ� ó��
    size_t start = 0;
    size_t end;
    while ((end = fileContent.find('\n', start)) != std::string::npos) {
        std::string line = fileContent.substr(start, end - start);
        ProcessLine(line); // �� �� ó��
        start = end + 1;
    }

    // ������ �� ó�� (EOF�� �ٹٲ����� ������ �ʴ� ���)
    if (start < fileContent.size()) {
        ProcessLine(fileContent.substr(start));
    }

    // 7. ���ҽ� ����
    UnmapViewOfFile(pMappedFile);
    CloseHandle(hMapping);
    CloseHandle(hFile);

    return 0;
}
