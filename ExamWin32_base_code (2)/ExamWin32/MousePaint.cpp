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
	// ���� ���콺�� ������ ���� ���� ���� �׸����� ����
	if (a_mixed_key & MK_LBUTTON)
	{
		LineTo(a_pos.x, a_pos.y);
		ShowDisplay();
	}
}

// ���콺 ���� ��ư�� ���
MOUSE_MESSAGE(OnLeftBtnDown, OnLeftBtnUp, OnMouseMove)

int main()
{
	SelectPenObject(RGB(0,0,255),3);
	ShowDisplay(); // ������ �����쿡 ����Ѵ�. 
	return 0;
}