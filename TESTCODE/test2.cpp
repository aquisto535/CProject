#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>
#include <Windows.h>


#pragma pack(push, 1) // 구조체의 정렬을 1바이트 단위로 설정
struct MyStruct {
    int id;
    double value;
    char name[32];

    MyStruct(int i, double v, const char* n) {
        id = i;
        value = v;
        strcpy_s(name, sizeof(name), n);
        name[sizeof(name) - 1] = '\0'; // null-terminate to avoid overflow
    }
};
#pragma pack(pop)

int main() {
    const char* fileName = "output.dat";
    std::ofstream outFile(fileName, std::ios::binary); // 이진 파일로 열기
    if (!outFile)
    {
		DWORD dwError = GetLastError();
        std::cerr << "Error: Could not open file for writing!" << std::endl;
        return 1;
    }

    MyStruct data(1, 123.45, "Sample Data");
    size_t structSize = sizeof(MyStruct);
    size_t targetFileSize = 572 * 1024; // 572KB
    size_t currentFileSize = 0;

    int counter = 1;

    // 데이터를 반복해서 파일에 작성
    while (currentFileSize < targetFileSize) {
        data.id = counter++;
        data.value += 0.01; // 데이터 값 변경
        strcpy_s(data.name, sizeof(data.name), "Updated Data"); 
        data.name[sizeof(data.name) - 1] = '\0';

        // 구조체 데이터를 이진 파일에 기록
        outFile.write(reinterpret_cast<const char*>(&data), structSize);
        currentFileSize += structSize;
    }

    outFile.close();

   
	SetFileAttributes(L"output.dat", FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_ENCRYPTED);


    std::cout << "File writing complete. File size: " << currentFileSize / 1024 << " KB" << std::endl;
    return 0;
}
