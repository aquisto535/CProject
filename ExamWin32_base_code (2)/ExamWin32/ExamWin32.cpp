#include "pch.h"
#include "tipsware.h"

// 이 프로그램은 특별한 메세지를 사용하지 않는다!
NOT_USE_MESSAGE;

int main()
{
	// 옆으로 구구단이 출력되게 하기 위해 2중 for문 사용. 
	for (int dan = 2; dan <= 9; dan++)
	{
		for (int i = 1; i <= 9; i++)
		{
			printf(10 +  (dan - 2)* 80, 10 + 20 * i, "%d * %d = %d", dan, i, dan * i);
		}
	}
    ShowDisplay(); // 정보를 윈도우에 출력한다. 
    return 0;
}
