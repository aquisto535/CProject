#include "pch.h"
#include "tipsware.h"

void LeftBtnDown(int a_mixed_key, POINT a_pos)
{
	if (a_mixed_key & MK_CONTROL) // 마우스 왼쪽 버튼과 컨트롤이 같이 눌림.
	{
		Ellipse(a_pos.x - 10, a_pos.y - 10, a_pos.x + 10, a_pos.y + 10, RGB(0, 255, 0));
	}
	else
	{
		Rectangle(a_pos.x - 10, a_pos.y - 10, a_pos.x + 10, a_pos.y + 10, RGB(255,0,255));

	}

	ShowDisplay();
}

// 마우스 왼쪽 버튼만 사용
MOUSE_MESSAGE(LeftBtnDown, NULL, NULL)

int main()
{

	TextOut(10, 10, RGB(0,0,255), "마우스를 클릭하면 사각형이 그려집니다");
	TextOut(10, 28, RGB(0,0,255), "컨트롤 키를 누른 상태에서 마우스를 클릭하면 타원이 그려집니다");


	ShowDisplay(); // 정보를 윈도우에 출력한다. 
	return 0;
}
