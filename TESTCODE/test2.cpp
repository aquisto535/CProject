#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>
#include <Windows.h>


#pragma pack(push, 1) // ����ü�� ������ 1����Ʈ ������ ����
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
    std::ofstream outFile(fileName, std::ios::binary); // ���� ���Ϸ� ����
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

    // �����͸� �ݺ��ؼ� ���Ͽ� �ۼ�
    while (currentFileSize < targetFileSize) {
        data.id = counter++;
        data.value += 0.01; // ������ �� ����
        strcpy_s(data.name, sizeof(data.name), "Updated Data"); 
        data.name[sizeof(data.name) - 1] = '\0';

        // ����ü �����͸� ���� ���Ͽ� ���
        outFile.write(reinterpret_cast<const char*>(&data), structSize);
        currentFileSize += structSize;
    }

    outFile.close();

   
	SetFileAttributes(L"output.dat", FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_ENCRYPTED);


    std::cout << "File writing complete. File size: " << currentFileSize / 1024 << " KB" << std::endl;
    return 0;
}
