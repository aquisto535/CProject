#include "pch.h"
#include "tipsware.h"

void OnLeftBtnDown(int a_mixed_key, POINT a_pos)
{
	if (a_pos.y >= 60 && a_pos.y <= 120) //�簢������ y = 60�� 120 ���̿� ��ġ�� ����.
	{
		for (int i = 0; i < 6; i++)
		{
			if ((a_pos.x >= 20 + i * 60) && (a_pos.x <= 20 + (i + 1) * 60))// ������ �����ϴ� ����. Ŭ�� �� Ŀ���� �簢�� �ȿ� �� �־��ٸ� 
			{
				Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 200, 255), RGB(0, 0, 255)); //�簢���� �ٽ� �׸�.
			}
			else
			{
				Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 100, 200), RGB(0, 0, 128)); //�簢���� �ٽ� �׸�. 
			}
		}
		//y���� ������ ��Ȳ���� x���� ��ġ�� ���� � �簢���� �����ߴ��� �� �� ����.

		ShowDisplay();

	}

}


// ���콺 ���� ��ư�� ���
MOUSE_MESSAGE(OnLeftBtnDown, NULL, NULL)	

int main()
{
	TextOut(10,10, RGB(0,0, 255), "�簢���� Ŭ���ϸ� ������ ����˴ϴ�~");

	for (int i = 0; i < 6; i++)
	{
		Rectangle(20 + i * 60 /* x��ǥ ������ */, 60/* y��ǥ ������ */, 20 + (i + 1) * 60/* x��ǥ ���� */, 120/* y��ǥ ������ */,
			RGB(0, 100, 200), RGB(0,0,128));
	}


	ShowDisplay(); // ������ �����쿡 ����Ѵ�. 
	return 0;
}