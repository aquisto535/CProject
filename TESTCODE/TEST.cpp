#include <windows.h>
#include <iostream>
#include <string>

int main() {
   //ANSI 표준 함수에서 파일 크기 탐색 방식
   FILE * fp = fopen("A.txt", "rb");

   fseek(fp, 0, SEEK_END); //fp파일 포인터를 끝으로 이동시킴

   DWORD sizeOfFile = ftell(fp); //ftell함수로 현재 위치 정보 얻어옴
    
   return 0;
}
