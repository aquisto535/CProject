#include "pch.h"
#include "tipsware.h"

void OnLeftBtnDown(int a_mixed_key, POINT a_pos) 
{

	// unsigned:음수 방지용. 음수가 나오면 양수로 바꿔줌. unsigned int 재정의는 음수 계산을 안 하기 위함. 
	unsigned int x = (unsigned int)(a_pos.x - 20) / 60 , y = (unsigned int)(a_pos.y - 60) / 60; // 조건문을 변수로 정리함. 코드 정리 차원
	                                                                                             
	if (x < 6 && y < 1)
	{
		for (int i = 0; i < 6; i++)
		{
			Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 200, 255), RGB(0, 0, 255)); //전체 사각형을 색깔을 바꿔 다시 그림.
			                                                                                      //클릭을 통해 전체가 바뀌는 느낌이 들면서 더 나은 UX를 제공할 수 있게 됨
		}

		Rectangle(20 + x * 60, 60, 20 + (x + 1) * 60, 120, RGB(0, 100, 200), RGB(0, 0, 128)); // 선택한 사각형의 색깔만 유지함. 
		                                                                                    

		ShowDisplay();

	}



}


// 마우스 왼쪽 버튼만 사용
MOUSE_MESSAGE(OnLeftBtnDown, NULL, NULL)

int main()
{	
	TextOut(10, 10, RGB(0, 0, 255), "사각형을 클릭하면 색상이 변경됩니다~");

	for (int i = 0; i < 6; i++)
	{
		Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 100, 200), RGB(0, 0, 128));
	}


	ShowDisplay(); // 정보를 윈도우에 출력한다. 
	return 0;
}