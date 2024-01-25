//#include "pch.h"
//#include "tipsware.h"
#include "stdio.h"

// 이 프로그램은 특별한 메세지를 사용하지 않는다!
//NOT_USE_MESSAGE;
//
//int main()
//{
//	ShowDisplay(); // 정보를 윈도우에 출력한다. 
//	return 0;
//}


int main()
{
	char data[15] = {0,0,2,0,1,1,0,0,2,1,0,2,0,0 ,0 };
	int i, x, y;

	for (int i = 0; i < 12; i++)
	{
		x = i % 5 + 1; //열로 나눈 나머지값 + 1 =>2차원 배열의 행
		y = i / 5 + 1; //열로 나눈 값 + 1 =>2차원 배열의 열

		printf("%d행 %d열에 " , x, y);
		if (data[i] == 1) printf("검은 돌이 놓여 있습니다.\n");
		else if (data[i] == 2) printf("흰 돌이 놓여 있습니다.\n");
		else printf("돌이 놓여 있지 않습니다.\n");

	}

	return 0;
}