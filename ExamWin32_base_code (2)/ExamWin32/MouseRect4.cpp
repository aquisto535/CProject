#include "pch.h"
#include "tipsware.h"

#define X_COUNT 6
#define Y_COUNT 3

#define GRID_SIZE 60

//이 파일에서 배운 점
//하나의 기능은 하나의 함수로 분리하여 사용한다!!

void DrawRect(char(*ap_data)[X_COUNT]) // 데이터를 받아 사각형을 그리는 기능.
{

	COLORREF fill_color[2] = { RGB(0, 0, 128), RGB(0, 0, 255) };

	//대상이 정해져 있을 경우 if문을 쓰기보다 테이블화하여 사용하는 것이 더 효율적인 방법이다!!
	for (unsigned int y = 0;  y < Y_COUNT; y++)
	{
		for (unsigned int x = 0; x < X_COUNT; x++)
		{
			Rectangle(x * GRID_SIZE, y * GRID_SIZE, (x +1)* GRID_SIZE + 1 , (y + 1) * GRID_SIZE + 1, RGB(0, 200, 255), fill_color[ap_data[y][x]]);
		}
	}

	ShowDisplay();

}

void OnLeftBtnDown(int a_mixed_key, POINT a_pos) // 데이터를 정돈하여 전달하는 기능.
{
	unsigned int x = a_pos.x / GRID_SIZE, y = a_pos.y / GRID_SIZE; // 사각형 중 적용 대상을 지정하기 위한 숫자.

	if (x < X_COUNT && y < Y_COUNT)
	{	
		char(*p)[X_COUNT] = (char(*)[X_COUNT])GetAppData(); //*p는 char [6]을 가리키는 포인터임. 첫번째 가로줄의 배열 데이터를 받아옴.
		
		p[y][x] = !p[y][x]; //(*(p + y))[x] = !(*(p + y))[x]; // 0이면 1로, 1이면 0으로 변경(클릭 시 색깔 변화 위함). 포인터 앞에 괄호를 씌운 이유는 포인터에 우선순위를 주기 위해서이다!!
		                    // 선택한 사각형 데이터 변경(0->1)

		DrawRect(p); // 선택한 사각형이 속한 행에서 사각형 6개의 데이터를 가져와 사각형을 그리는 함수에 전달함. 
	}

}


// 마우스 왼쪽 버튼만 사용
MOUSE_MESSAGE(OnLeftBtnDown, NULL, NULL)

int main()
{
	TextOut(10, 10, RGB(0, 0, 255), "사각형을 클릭하면 색상이 변경됩니다~");

	char state[Y_COUNT][X_COUNT] = { {0,},  }; //6바이트 선언. 데이터 테이블화 시킴. 2차원 배열 6개 길이를 가진 배열이 3개 있음.
	//char state[18] = {{1,2,3,4,5,6}, {1,2,3,4,5,6}, {1,2,3,4,5,6}} 위의 배열을 1차원으로 바꾸면 이와 같은 형태가 됨.
	SetAppData(state, sizeof(state)); // 내부 데이터에 18바이트 넘김. 18개의 사각형 데이터 
	DrawRect(state);

	////////////////////////////중복되어 함수로 나간 부분/////////////////////////
	
	//for (int y = 0; y < 3; y++)
	//{
	//	for (int x = 0; x < 6; x++)
	//	{
	//		Rectangle(x * 60, y * 60, (x + 1) * 60, (y + 1) * 60, RGB(0, 100, 200), RGB(0, 0, 128));
	//	}
	//}

	//////////////////////////////////////////////////////////////////////////	

	ShowDisplay(); // 정보를 윈도우에 출력한다. 
	return 0;
}