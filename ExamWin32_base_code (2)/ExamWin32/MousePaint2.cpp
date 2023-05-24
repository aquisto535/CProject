#include "pch.h"
#include "tipsware.h"


// 전역 변수 대신 구조체를 선언. 
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
		p_data->g_start_pos = a_pos; // 선 그리기의 시작 점을 설정한다.
	}

}

void OnLeftBtnUp(int a_mixed_key, POINT a_pos)
{	
	AppData* p_data = (AppData*)GetAppData();
	if (p_data->is_clicked == 1)
	{
		p_data->is_clicked = 0;
		Line(p_data->g_start_pos.x, p_data->g_start_pos.y, a_pos.x, a_pos.y); // 이전 선 그리기의 끝점에서 a_pos의 위치까지 선을 연결한다.
		ShowDisplay();
	}
	
}

void OnMouseMove(int a_mixed_key, POINT a_pos)
{
	// 왼쪽 마우스를 누르고 있을 때만 선을 그리도록 설정
	AppData* p_data = (AppData*)GetAppData();
	if (p_data->is_clicked == 1)
	{
		Line(p_data->g_start_pos.x, p_data->g_start_pos.y, a_pos.x, a_pos.y);
		p_data->g_start_pos = a_pos;// 현재 점이 다음 점의 시작점이 될 수 있도록 점을 계속 바꿔줌. 이전에는 시작점이 고정되어 있었음.
		ShowDisplay();
	}
}

// 마우스 왼쪽 버튼만 사용
MOUSE_MESSAGE(OnLeftBtnDown, OnLeftBtnUp, OnMouseMove)

int main()
{	
	AppData	data = { {0,0}, 0 };
	SetAppData(&data, sizeof(AppData));

	SelectPenObject(RGB(0, 0, 255), 3);
	ShowDisplay(); // 정보를 윈도우에 출력한다. 
	return 0;
}