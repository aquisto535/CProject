#include "pch.h"
#include "tipsware.h"

void OnLeftBtnDown(int a_mixed_key, POINT a_pos)
{
	MoveTo(a_pos.x, a_pos.y);
	ShowDisplay();
}

void OnLeftBtnUp(int a_mixed_key, POINT a_pos)
{
	LineTo(a_pos.x, a_pos.y);
	ShowDisplay();
}

void OnMouseMove(int a_mixed_key, POINT a_pos)
{	
	// 왼쪽 마우스를 누르고 있을 때만 선을 그리도록 설정
	if (a_mixed_key & MK_LBUTTON)
	{
		LineTo(a_pos.x, a_pos.y);
		ShowDisplay();
	}
}

// 마우스 왼쪽 버튼만 사용
MOUSE_MESSAGE(OnLeftBtnDown, OnLeftBtnUp, OnMouseMove)

int main()
{
	SelectPenObject(RGB(0,0,255),3);
	ShowDisplay(); // 정보를 윈도우에 출력한다. 
	return 0;
}