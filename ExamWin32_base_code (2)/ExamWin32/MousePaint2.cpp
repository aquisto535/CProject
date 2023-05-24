#include "pch.h"
#include "tipsware.h"


// ���� ���� ��� ����ü�� ����. 
struct AppData
{
	POINT g_start_pos;
	char is_clicked;
};


void OnLeftBtnDown(int a_mixed_key, POINT a_pos)
{
	AppData* p_data = (AppData*)GetAppData();
	if (p_data->is_clicked == 0)
	{
		p_data->is_clicked = 1;
		p_data->g_start_pos = a_pos; // �� �׸����� ���� ���� �����Ѵ�.
	}

}

void OnLeftBtnUp(int a_mixed_key, POINT a_pos)
{	
	AppData* p_data = (AppData*)GetAppData();
	if (p_data->is_clicked == 1)
	{
		p_data->is_clicked = 0;
		Line(p_data->g_start_pos.x, p_data->g_start_pos.y, a_pos.x, a_pos.y); // ���� �� �׸����� �������� a_pos�� ��ġ���� ���� �����Ѵ�.
		ShowDisplay();
	}
	
}

void OnMouseMove(int a_mixed_key, POINT a_pos)
{
	// ���� ���콺�� ������ ���� ���� ���� �׸����� ����
	AppData* p_data = (AppData*)GetAppData();
	if (p_data->is_clicked == 1)
	{
		Line(p_data->g_start_pos.x, p_data->g_start_pos.y, a_pos.x, a_pos.y);
		p_data->g_start_pos = a_pos;// ���� ���� ���� ���� �������� �� �� �ֵ��� ���� ��� �ٲ���. �������� �������� �����Ǿ� �־���.
		ShowDisplay();
	}
}

// ���콺 ���� ��ư�� ���
MOUSE_MESSAGE(OnLeftBtnDown, OnLeftBtnUp, OnMouseMove)

int main()
{	
	AppData	data = { {0,0}, 0 };
	SetAppData(&data, sizeof(AppData));

	SelectPenObject(RGB(0, 0, 255), 3);
	ShowDisplay(); // ������ �����쿡 ����Ѵ�. 
	return 0;
}