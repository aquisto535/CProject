#include "pch.h"
#include "tipsware.h"

#define MAX_COUNT  100

// ���� ���� ��� ����ü�� ����. 
struct AppData
{
	POINT g_start_pos;
	RECT r_list[MAX_COUNT];
	char is_clicked;
	int r_count;
};


void DrawRect(AppData *ap_data)
{
	Clear();
	RECT* p = ap_data->r_list; // ����ü�� �迭�� ���� ���� ���� ������ ������ ���� �ֱ� ���� ������ ������ �����ϴ� ���� �� ����! 

	for (int i = 0; i < ap_data->r_count; i++, p++)
	{
		Rectangle(p->left, p->top, p->right, p->bottom);
	}
}

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

		if (p_data->is_clicked < MAX_COUNT)
		{
			p_data->r_list[p_data->r_count].left = p_data->g_start_pos.x;
			p_data->r_list[p_data->r_count].top = p_data->g_start_pos.y;		
			p_data->r_list[p_data->r_count].right = a_pos.x;
			p_data->r_list[p_data->r_count].bottom = a_pos.y;
			p_data->r_count++;
		}
		//Clear();
		DrawRect(p_data);// ���콺�� ������ ���� �׸��� �����ǵ��� �׸��� �׸�.
		//Rectangle(p_data->g_start_pos.x, p_data->g_start_pos.y, a_pos.x, a_pos.y); // ���� �� �׸����� �������� a_pos�� ��ġ���� ���� �����Ѵ�.
		ShowDisplay();
	}

}

void OnMouseMove(int a_mixed_key, POINT a_pos)
{
	// ���� ���콺�� ������ ���� ���� ���� �׸����� ����
	AppData* p_data = (AppData*)GetAppData();
	if (p_data->is_clicked == 1)
	{	
		DrawRect(p_data); //������ �׷ȴ� �簢�� ����.
		//Clear(); // ������ �׷ȴ� �簢���� ����� ���ο� �簢���� �׸�
		Rectangle(p_data->g_start_pos.x, p_data->g_start_pos.y, a_pos.x, a_pos.y);
		ShowDisplay();
	}
}

// ���콺 ���� ��ư�� ���
MOUSE_MESSAGE(OnLeftBtnDown, OnLeftBtnUp, OnMouseMove)

int main()
{
	AppData	data = { {0,0}, 0,0 };
	SetAppData(&data, sizeof(AppData));

	SelectPenObject(RGB(0, 0, 255), 3);
	SelectStockObject(NULL_BRUSH); // ��ġ�� �簢�� �����ϵ��� ����.

	ShowDisplay(); // ������ �����쿡 ����Ѵ�. 
	return 0;
}