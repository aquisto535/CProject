#include "pch.h"
#include "tipsware.h"

#define X_COUNT 6
#define Y_COUNT 3

#define GRID_SIZE 60

//�� ���Ͽ��� ��� ��
//�ϳ��� ����� �ϳ��� �Լ��� �и��Ͽ� ����Ѵ�!!

void DrawRect(char(*ap_data)[X_COUNT]) // �����͸� �޾� �簢���� �׸��� ���.
{

	COLORREF fill_color[2] = { RGB(0, 0, 128), RGB(0, 0, 255) };

	//����� ������ ���� ��� if���� ���⺸�� ���̺�ȭ�Ͽ� ����ϴ� ���� �� ȿ������ ����̴�!!
	for (unsigned int y = 0;  y < Y_COUNT; y++)
	{
		for (unsigned int x = 0; x < X_COUNT; x++)
		{
			Rectangle(x * GRID_SIZE, y * GRID_SIZE, (x +1)* GRID_SIZE + 1 , (y + 1) * GRID_SIZE + 1, RGB(0, 200, 255), fill_color[ap_data[y][x]]);
		}
	}

	ShowDisplay();

}

void OnLeftBtnDown(int a_mixed_key, POINT a_pos) // �����͸� �����Ͽ� �����ϴ� ���.
{
	unsigned int x = a_pos.x / GRID_SIZE, y = a_pos.y / GRID_SIZE; // �簢�� �� ���� ����� �����ϱ� ���� ����.

	if (x < X_COUNT && y < Y_COUNT)
	{	
		char(*p)[X_COUNT] = (char(*)[X_COUNT])GetAppData(); //*p�� char [6]�� ����Ű�� ��������. ù��° �������� �迭 �����͸� �޾ƿ�.
		
		p[y][x] = !p[y][x]; //(*(p + y))[x] = !(*(p + y))[x]; // 0�̸� 1��, 1�̸� 0���� ����(Ŭ�� �� ���� ��ȭ ����). ������ �տ� ��ȣ�� ���� ������ �����Ϳ� �켱������ �ֱ� ���ؼ��̴�!!
		                    // ������ �簢�� ������ ����(0->1)

		DrawRect(p); // ������ �簢���� ���� �࿡�� �簢�� 6���� �����͸� ������ �簢���� �׸��� �Լ��� ������. 
	}

}


// ���콺 ���� ��ư�� ���
MOUSE_MESSAGE(OnLeftBtnDown, NULL, NULL)

int main()
{
	TextOut(10, 10, RGB(0, 0, 255), "�簢���� Ŭ���ϸ� ������ ����˴ϴ�~");

	char state[Y_COUNT][X_COUNT] = { {0,},  }; //6����Ʈ ����. ������ ���̺�ȭ ��Ŵ. 2���� �迭 6�� ���̸� ���� �迭�� 3�� ����.
	//char state[18] = {{1,2,3,4,5,6}, {1,2,3,4,5,6}, {1,2,3,4,5,6}} ���� �迭�� 1�������� �ٲٸ� �̿� ���� ���°� ��.
	SetAppData(state, sizeof(state)); // ���� �����Ϳ� 18����Ʈ �ѱ�. 18���� �簢�� ������ 
	DrawRect(state);

	////////////////////////////�ߺ��Ǿ� �Լ��� ���� �κ�/////////////////////////
	
	//for (int y = 0; y < 3; y++)
	//{
	//	for (int x = 0; x < 6; x++)
	//	{
	//		Rectangle(x * 60, y * 60, (x + 1) * 60, (y + 1) * 60, RGB(0, 100, 200), RGB(0, 0, 128));
	//	}
	//}

	//////////////////////////////////////////////////////////////////////////	

	ShowDisplay(); // ������ �����쿡 ����Ѵ�. 
	return 0;
}