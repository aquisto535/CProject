#include "pch.h"
#include "tipsware.h"
#include <math.h>

NOT_USE_MESSAGE;

int main()
{	
	int y;

	// ���� �� �׸���
	Line(0,100, 720, 100, RGB(200,200,200), 1, PS_DOT);
	Line(360,0, 360, 200);


	SelectPenObject(RGB(0,0, 255), 3);
	MoveTo(0, 100);
	// ���� ������ ���� sin ���� ��
	for (int degree = 0; degree < 720; degree++)
	{
		y =  100 - 1 * (int)(sin(degree * 3.14 / 180) * 100);
		LineTo(degree, y);
	}


	SelectPenObject(RGB(255, 0, 0), 3);
	MoveTo(0, 100);
	// ���� ������ ���� sin ���� ��
	for (int degree = 0; degree < 720; degree++)
	{
		y = 100 - 1 * (int)(cos(degree * 3.14 / 180) * 100);
		LineTo(degree, y);
	}


	ShowDisplay(); // ������ �����쿡 ����Ѵ�. 
	return 0;
}
