#include "pch.h"
#include "tipsware.h"

#define X_COUNT 12
#define Y_COUNT 12

#define GRID_SIZE 30

//��ۿ� �ʿ��� ������ + �� ������ ���� ��Ƶ�. �̸� �����ϱ� ���� ����ü�� �����.
struct AppData
{
	char state[Y_COUNT][X_COUNT]; // �� �簢������ �ƴ��� �ľ� ����
	char step; // ���� ����
};

void OnLeftBtnDown(int a_mixed_key, POINT a_pos)
{
	unsigned int x = a_pos.x / GRID_SIZE, y = a_pos.y / GRID_SIZE; // ���� ����� �����ϱ� ���� ����.

	AppData* p_data = (AppData*)GetAppData();

	if (x < X_COUNT && y < Y_COUNT && !p_data->state[y][x]) //!p_data->state[y][x]�� �ٽ� Ŭ������ �� �׷����� ���� ���� ������. p_data->state[y][x]�� 0�̶�� �ǹ̴� ������ Ŭ���� ���� ���ٴ� �̾߱���.
	{
		p_data->state[y][x] = p_data->step + 1; //p_data->state[y][x] = 1;

		p_data->step = !p_data->step; // p_data->state[y][x]�� �����ϱ� ���� ����. p_data->step = 1;

		ShowDisplay();
	} //Ŭ���� ��ġ�� ���� �׸����� ����.

}


// ���콺 ���� ��ư�� ���
MOUSE_MESSAGE(OnLeftBtnDown, NULL, NULL)

int main()
{
	TextOut(10, 10, RGB(0, 0, 255), "�簢���� Ŭ���ϸ� ������ ����˴ϴ�~");

	AppData data;
	memset(&data, 0, sizeof(data));

	SetAppData(&data, sizeof(data)); // ���� �����Ϳ� 6����Ʈ �ѱ�.

	ShowDisplay(); // ������ �����쿡 ����Ѵ�. 
	return 0;
}