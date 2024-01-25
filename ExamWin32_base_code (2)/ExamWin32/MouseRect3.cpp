#include "pch.h"
#include "tipsware.h"

//�� ���Ͽ��� ��� ��
// - !������ ���� ���� ���� �ݴ�� �ڹٲ� �� �ִ�
// - ����� ������ ���� ��� if���� ���⺸�� ���̺�ȭ�Ͽ� ����ϴ� ���� �� ȿ������ ����̴�

void OnLeftBtnDown(int a_mixed_key, POINT a_pos)
{

	// unsigned:���� ������. ������ ������ ����� �ٲ���. unsigned int �����Ǵ� ���� ����� �� �ϱ� ����. 
	unsigned int x = (unsigned int)(a_pos.x - 20) / 60, y = (unsigned int)(a_pos.y - 60) / 60; // �簢�� �� ���� ����� �����ϱ� ���� ����.

	if (x < 6 && y < 1)
	{	
		char *p_data = (char *)GetAppData();
		p_data[x] = !p_data[x]; // ���� ���� �ڹٲ�. 0->1. ������ �簢���� ���� ��ȭ��Ű��, �� ���� �������� ���� ��ȭ�� �ش�.
		                        // ������ �簢���� ��� 0�� ��Ȳ���� ���õ� �簢���� 1�� ���� ������ ��. ��Ʈ�� ����.

		COLORREF border_color[2] = { RGB(0, 100, 200), RGB(0, 200, 255) };
		COLORREF fill_color[2] = { RGB(0, 0, 128), RGB(0, 0, 255) };

		//����� ������ ���� ��� if���� ���⺸�� ���̺�ȭ�Ͽ� ����ϴ� ���� �� ȿ������ ����̴�!!
		for (int i = 0; i < 6; i++)
		{
			Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, border_color[p_data[i]], fill_color[p_data[i]]);
		}

		//�ݺ��� �ȿ� if���� ��� �־� ���� �ڵ� ��������� �ƴ�.
		//for (int i = 0; i < 6; i++)
		//{
		//	if(p_data[i])
		//		Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 200, 255), RGB(0, 0, 255)); //��ü �簢���� ������ �ٲ� �ٽ� �׸�.
		//	else
		//		Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 100, 200), RGB(0, 0, 128)); // ������ �簢���� ������ �ٲ�.
		//}

		

		ShowDisplay();

	}



}


// ���콺 ���� ��ư�� ���
MOUSE_MESSAGE(OnLeftBtnDown, NULL, NULL)

int main()
{
	TextOut(10, 10, RGB(0, 0, 255), "�簢���� Ŭ���ϸ� ������ ����˴ϴ�~");

	char state[6] = { 0, }; //6����Ʈ ����. �簢�� ������ ���̺�ȭ ��Ŵ.
	SetAppData(state, sizeof(state)); // ���� �����Ϳ� 6����Ʈ �ѱ�.
	for (int i = 0; i < 6; i++)
	{
		Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 100, 200), RGB(0, 0, 128));
	}


	ShowDisplay(); // ������ �����쿡 ����Ѵ�. 
	return 0;
}