#include "pch.h"
#include "tipsware.h"

void LeftBtnDown(int a_mixed_key, POINT a_pos)
{
	if (a_mixed_key & MK_CONTROL) // ���콺 ���� ��ư�� ��Ʈ���� ���� ����.
	{
		Ellipse(a_pos.x - 10, a_pos.y - 10, a_pos.x + 10, a_pos.y + 10, RGB(0, 255, 0));
	}
	else
	{
		Rectangle(a_pos.x - 10, a_pos.y - 10, a_pos.x + 10, a_pos.y + 10, RGB(255,0,255));

	}

	ShowDisplay();
}

// ���콺 ���� ��ư�� ���
MOUSE_MESSAGE(LeftBtnDown, NULL, NULL)

int main()
{

	TextOut(10, 10, RGB(0,0,255), "���콺�� Ŭ���ϸ� �簢���� �׷����ϴ�");
	TextOut(10, 28, RGB(0,0,255), "��Ʈ�� Ű�� ���� ���¿��� ���콺�� Ŭ���ϸ� Ÿ���� �׷����ϴ�");


	ShowDisplay(); // ������ �����쿡 ����Ѵ�. 
	return 0;
}
