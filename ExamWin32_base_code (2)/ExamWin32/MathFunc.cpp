#include "pch.h"
#include "tipsware.h"
#include <math.h>

NOT_USE_MESSAGE;

int main()
{	
	int y;

	// 가로 축 그리기
	Line(0,100, 720, 100, RGB(200,200,200), 1, PS_DOT);
	Line(360,0, 360, 200);


	SelectPenObject(RGB(0,0, 255), 3);
	MoveTo(0, 100);
	// 현재 각도에 대한 sin 라디안 값
	for (int degree = 0; degree < 720; degree++)
	{
		y =  100 - 1 * (int)(sin(degree * 3.14 / 180) * 100);
		LineTo(degree, y);
	}


	SelectPenObject(RGB(255, 0, 0), 3);
	MoveTo(0, 100);
	// 현재 각도에 대한 sin 라디안 값
	for (int degree = 0; degree < 720; degree++)
	{
		y = 100 - 1 * (int)(cos(degree * 3.14 / 180) * 100);
		LineTo(degree, y);
	}


	ShowDisplay(); // 정보를 윈도우에 출력한다. 
	return 0;
}
