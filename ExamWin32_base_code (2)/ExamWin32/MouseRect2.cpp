#include "pch.h"
#include "tipsware.h"

void OnLeftBtnDown(int a_mixed_key, POINT a_pos) 
{

	// unsigned:���� ������. ������ ������ ����� �ٲ���. unsigned int �����Ǵ� ���� ����� �� �ϱ� ����. 
	unsigned int x = (unsigned int)(a_pos.x - 20) / 60 , y = (unsigned int)(a_pos.y - 60) / 60; // ���ǹ��� ������ ������. �ڵ� ���� ����
	                                                                                             
	if (x < 6 && y < 1)
	{
		for (int i = 0; i < 6; i++)
		{
			Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 200, 255), RGB(0, 0, 255)); //��ü �簢���� ������ �ٲ� �ٽ� �׸�.
			                                                                                      //Ŭ���� ���� ��ü�� �ٲ�� ������ ��鼭 �� ���� UX�� ������ �� �ְ� ��
		}

		Rectangle(20 + x * 60, 60, 20 + (x + 1) * 60, 120, RGB(0, 100, 200), RGB(0, 0, 128)); // ������ �簢���� ���� ������. 
		                                                                                    

		ShowDisplay();

	}



}


// ���콺 ���� ��ư�� ���
MOUSE_MESSAGE(OnLeftBtnDown, NULL, NULL)

int main()
{	
	TextOut(10, 10, RGB(0, 0, 255), "�簢���� Ŭ���ϸ� ������ ����˴ϴ�~");

	for (int i = 0; i < 6; i++)
	{
		Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 100, 200), RGB(0, 0, 128));
	}


	ShowDisplay(); // ������ �����쿡 ����Ѵ�. 
	return 0;
}