#include "pch.h"
#include "tipsware.h"

void OnLeftBtnDown(int a_mixed_key, POINT a_pos)
{
	if (a_pos.y >= 60 && a_pos.y <= 120) //사각형들이 y = 60와 120 사이에 위치해 있음.
	{
		for (int i = 0; i < 6; i++)
		{
			if ((a_pos.x >= 20 + i * 60) && (a_pos.x <= 20 + (i + 1) * 60))// 색깔을 결정하는 조건. 클릭 시 커서가 사각형 안에 들어가 있었다면 
			{
				Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 200, 255), RGB(0, 0, 255)); //사각형을 다시 그림.
			}
			else
			{
				Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 100, 200), RGB(0, 0, 128)); //사각형을 다시 그림. 
			}
		}
		//y축이 정해진 상황에서 x축의 위치를 통해 어떤 사각형을 선택했는지 알 수 있음.

		ShowDisplay();

	}

}


// 마우스 왼쪽 버튼만 사용
MOUSE_MESSAGE(OnLeftBtnDown, NULL, NULL)	

int main()
{
	TextOut(10,10, RGB(0,0, 255), "사각형을 클릭하면 색상이 변경됩니다~");

	for (int i = 0; i < 6; i++)
	{
		Rectangle(20 + i * 60 /* x좌표 시작점 */, 60/* y좌표 시작점 */, 20 + (i + 1) * 60/* x좌표 종점 */, 120/* y좌표 시작점 */,
			RGB(0, 100, 200), RGB(0,0,128));
	}


	ShowDisplay(); // 정보를 윈도우에 출력한다. 
	return 0;
}