#include "pch.h"
#include "tipsware.h"

#define X_COUNT 19
#define Y_COUNT 19

#define GRID_SIZE 20 //���� ����

//��ۿ� �ʿ��� ������ + �� ������ ���� ��Ƶ�.
struct AppData
{
	char state[Y_COUNT][X_COUNT]; // �� �簢��, �� ��, ���� �� �ľ� ����
	char step;
};

void DrawRect(AppData* ap_data)
{	
	int nCount = 0;
	COLORREF fill_color[2] = { RGB(0, 0, 0), RGB(255, 255, 255) };

	//����� ������ ���� ��� if���� ���⺸�� ���̺�ȭ�Ͽ� ����ϴ� ���� �� ȿ������ ����̴�!!
	for (unsigned int y = 0; y < Y_COUNT; y++)
	{
		for (unsigned int x = 0; x < X_COUNT; x++)
		{
			if (ap_data->state[y][x]) //ap_data->state[y][x] ���� 0���� ū ����
			{
				Ellipse(x * GRID_SIZE, y * GRID_SIZE, (x + 1) * GRID_SIZE + 1, (y + 1) * GRID_SIZE + 1, RGB(0, 0, 0), fill_color[ap_data->state[y][x] - 1]);
			}

			//���� ���θ� Ȯ���� �ڵ� ��ġ
		}


	}	

	ShowDisplay();

}

void OnLeftBtnDown(int a_mixed_key, POINT a_pos)
{
	unsigned int x = a_pos.x / GRID_SIZE, y = a_pos.y / GRID_SIZE; // ���� ����� �����ϱ� ���� ����.

	AppData* p_data = (AppData*)GetAppData();

	if (x < X_COUNT && y < Y_COUNT && !p_data->state[y][x]) //!p_data->state[y][x]�� �ٽ� Ŭ������ �� �׷����� ���� ���� ������.
	{
		p_data->state[y][x] = p_data->step + 1;

		COLORREF fill_color[2] = { RGB(0, 0, 0), RGB(255, 255, 255) };

		Ellipse(x * GRID_SIZE, y * GRID_SIZE, (x + 1) * GRID_SIZE + 1, (y + 1) * GRID_SIZE + 1, RGB(0, 0, 0), fill_color[p_data->state[y][x] - 1]);

		p_data->step = !p_data->step; // p_data->state[y][x]�� �����ϱ� ���� ����

		DrawRect(p_data); //�ּҰ��� ������ �ִ� ������ �����̱� ������ �ּҰ��� �䱸�� ���ڿ��� ������.
	}

}


// ���콺 ���� ��ư�� ���
MOUSE_MESSAGE(OnLeftBtnDown, NULL, NULL)

int main()
{
	TextOut(10, 10, RGB(0, 0, 255), "�簢���� Ŭ���ϸ� ������ ����˴ϴ�~");

	AppData data;
	memset(&data, 0, sizeof(data));

	SetAppData(&data, sizeof(data)); // ���� �����Ϳ� 6����Ʈ �ѱ�.

	for (unsigned int y = 0; y < Y_COUNT - 1; y++) //�簢�� �׸��� �ڵ�. �簢���� �Űܼ� �ٵ������� ���̵��� ������.
	{
		for (unsigned int x = 0; x < X_COUNT - 1; x++)
		{
			Rectangle(GRID_SIZE / 2 + x * GRID_SIZE, GRID_SIZE / 2 + y * GRID_SIZE, GRID_SIZE / 2 + (x + 1) * GRID_SIZE + 1,
				GRID_SIZE / 2 + (y + 1) * GRID_SIZE + 1, RGB(0, 0, 0), RGB(244, 176, 77));
		}
	}// �ٵ����� �ٽ� �׸��� ���� ������ ó���� �׸�.

	ShowDisplay(); // ������ �����쿡 ����Ѵ�. 
	return 0;
}