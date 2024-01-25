#include "pch.h"
#include "tipsware.h"

//이 파일에서 배운 점
// - !연산을 통해 변수 값을 반대로 뒤바꿀 수 있다
// - 대상이 정해져 있을 경우 if문을 쓰기보다 테이블화하여 사용하는 것이 더 효율적인 방법이다

void OnLeftBtnDown(int a_mixed_key, POINT a_pos)
{

	// unsigned:음수 방지용. 음수가 나오면 양수로 바꿔줌. unsigned int 재정의는 음수 계산을 안 하기 위함. 
	unsigned int x = (unsigned int)(a_pos.x - 20) / 60, y = (unsigned int)(a_pos.y - 60) / 60; // 사각형 중 적용 대상을 지정하기 위한 숫자.

	if (x < 6 && y < 1)
	{	
		char *p_data = (char *)GetAppData();
		p_data[x] = !p_data[x]; // 값을 서로 뒤바꿈. 0->1. 선택한 사각형의 값을 변화시키고, 그 값을 기준으로 색깔에 변화를 준다.
		                        // 나머지 사각형은 모두 0인 상황에서 선택된 사각형만 1의 값을 가지게 됨. 비트와 유사.

		COLORREF border_color[2] = { RGB(0, 100, 200), RGB(0, 200, 255) };
		COLORREF fill_color[2] = { RGB(0, 0, 128), RGB(0, 0, 255) };

		//대상이 정해져 있을 경우 if문을 쓰기보다 테이블화하여 사용하는 것이 더 효율적인 방법이다!!
		for (int i = 0; i < 6; i++)
		{
			Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, border_color[p_data[i]], fill_color[p_data[i]]);
		}

		//반복문 안에 if문이 들어 있어 좋은 코드 구성방식이 아님.
		//for (int i = 0; i < 6; i++)
		//{
		//	if(p_data[i])
		//		Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 200, 255), RGB(0, 0, 255)); //전체 사각형을 색깔을 바꿔 다시 그림.
		//	else
		//		Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 100, 200), RGB(0, 0, 128)); // 선택한 사각형의 색깔을 바꿈.
		//}

		

		ShowDisplay();

	}



}


// 마우스 왼쪽 버튼만 사용
MOUSE_MESSAGE(OnLeftBtnDown, NULL, NULL)

int main()
{
	TextOut(10, 10, RGB(0, 0, 255), "사각형을 클릭하면 색상이 변경됩니다~");

	char state[6] = { 0, }; //6바이트 선언. 사각형 데이터 테이블화 시킴.
	SetAppData(state, sizeof(state)); // 내부 데이터에 6바이트 넘김.
	for (int i = 0; i < 6; i++)
	{
		Rectangle(20 + i * 60, 60, 20 + (i + 1) * 60, 120, RGB(0, 100, 200), RGB(0, 0, 128));
	}


	ShowDisplay(); // 정보를 윈도우에 출력한다. 
	return 0;
}