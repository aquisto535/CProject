#include "pch.h"
#include "tipsware.h"

#define MAX_COUNT  100

// 전역 변수 대신 구조체를 선언. 
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
	RECT* p = ap_data->r_list; // 구조체를 배열로 받을 때는 내부 변수에 일일이 값을 넣기 보다 포인터 변수를 선언하는 편이 더 낫다! 

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
		p_data->g_start_pos = a_pos; // 선 그리기의 시작 점을 설정한다.
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
		DrawRect(p_data);// 마우스를 놓았을 때도 그림이 유지되도록 그림을 그림.
		//Rectangle(p_data->g_start_pos.x, p_data->g_start_pos.y, a_pos.x, a_pos.y); // 이전 선 그리기의 끝점에서 a_pos의 위치까지 선을 연결한다.
		ShowDisplay();
	}

}

void OnMouseMove(int a_mixed_key, POINT a_pos)
{
	// 왼쪽 마우스를 누르고 있을 때만 선을 그리도록 설정
	AppData* p_data = (AppData*)GetAppData();
	if (p_data->is_clicked == 1)
	{	
		DrawRect(p_data); //이전에 그렸던 사각형 유지.
		//Clear(); // 이전에 그렸던 사각형을 지우고 새로운 사각형을 그림
		Rectangle(p_data->g_start_pos.x, p_data->g_start_pos.y, a_pos.x, a_pos.y);
		ShowDisplay();
	}
}

// 마우스 왼쪽 버튼만 사용
MOUSE_MESSAGE(OnLeftBtnDown, OnLeftBtnUp, OnMouseMove)

int main()
{
	AppData	data = { {0,0}, 0,0 };
	SetAppData(&data, sizeof(AppData));

	SelectPenObject(RGB(0, 0, 255), 3);
	SelectStockObject(NULL_BRUSH); // 겹치는 사각형 가능하도록 설정.

	ShowDisplay(); // 정보를 윈도우에 출력한다. 
	return 0;
}