#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>
#include <map>

#pragma pack(push, 1) // 구조체 정렬 1바이트 단위로 설정
struct MyStruct {
    int id;
    double value;
    char name[32];
};
#pragma pack(pop)



int main() 
{
    clock_t start, finish;
    double duration;

	start = clock();

    const char* fileName = "output.dat";
    std::ifstream inFile(fileName, std::ios::binary); // 이진 파일 읽기 모드로 열기
    if (!inFile) {
        std::cerr << "Error: Could not open file for reading!" << std::endl;
        return 1;
    }

    MyStruct data;
    size_t structSize = sizeof(MyStruct);

	std::map<int, MyStruct> dataMap;

    // 파일 크기 확인
    inFile.seekg(0, std::ios::end);
    size_t fileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg);

    size_t numRecords = fileSize / structSize;
    std::cout << "Number of records in the file: " << numRecords << std::endl;

    // 데이터를 한 줄씩 읽어서 출력
    int counter = 0;
    while (inFile.read(reinterpret_cast<char*>(&data), structSize)) 
    {
		dataMap[data.id] = data;
    }

    inFile.close();

    finish = clock();

    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("%f초\n", duration);

    printf("구조체 갯수 : %d\n", dataMap.size());

    std::cout << "File reading complete." << std::endl;
    return 0;
}
