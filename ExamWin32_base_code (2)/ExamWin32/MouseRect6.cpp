#include "pch.h"
#include "tipsware.h"

#define X_COUNT 19
#define Y_COUNT 19

#define GRID_SIZE 20 //폭과 넓이

//토글에 필요한 데이터 + 원 데이터 같이 담아둠.
struct AppData
{
	char state[Y_COUNT][X_COUNT]; // 빈 사각형, 흰 원, 검은 원 파악 정보
	char step;
};

void DrawRect(AppData* ap_data)
{	
	int nCount = 0;
	COLORREF fill_color[2] = { RGB(0, 0, 0), RGB(255, 255, 255) };

	//대상이 정해져 있을 경우 if문을 쓰기보다 테이블화하여 사용하는 것이 더 효율적인 방법이다!!
	for (unsigned int y = 0; y < Y_COUNT; y++)
	{
		for (unsigned int x = 0; x < X_COUNT; x++)
		{
			if (ap_data->state[y][x]) //ap_data->state[y][x] 값이 0보다 큰 조건
			{
				Ellipse(x * GRID_SIZE, y * GRID_SIZE, (x + 1) * GRID_SIZE + 1, (y + 1) * GRID_SIZE + 1, RGB(0, 0, 0), fill_color[ap_data->state[y][x] - 1]);
			}

			//빙고 여부를 확인할 코드 위치
		}


	}	

	ShowDisplay();

}

void OnLeftBtnDown(int a_mixed_key, POINT a_pos)
{
	unsigned int x = a_pos.x / GRID_SIZE, y = a_pos.y / GRID_SIZE; // 적용 대상을 지정하기 위한 숫자.

	AppData* p_data = (AppData*)GetAppData();

	if (x < X_COUNT && y < Y_COUNT && !p_data->state[y][x]) //!p_data->state[y][x]는 다시 클릭했을 때 그려지는 현상 방지 위함임.
	{
		p_data->state[y][x] = p_data->step + 1;

		COLORREF fill_color[2] = { RGB(0, 0, 0), RGB(255, 255, 255) };

		Ellipse(x * GRID_SIZE, y * GRID_SIZE, (x + 1) * GRID_SIZE + 1, (y + 1) * GRID_SIZE + 1, RGB(0, 0, 0), fill_color[p_data->state[y][x] - 1]);

		p_data->step = !p_data->step; // p_data->state[y][x]을 조작하기 위한 변수

		DrawRect(p_data); //주소값을 가지고 있는 포인터 변수이기 때문에 주소값을 요구한 인자에도 부합함.
	}

}


// 마우스 왼쪽 버튼만 사용
MOUSE_MESSAGE(OnLeftBtnDown, NULL, NULL)

int main()
{
	TextOut(10, 10, RGB(0, 0, 255), "사각형을 클릭하면 색상이 변경됩니다~");

	AppData data;
	memset(&data, 0, sizeof(data));

	SetAppData(&data, sizeof(data)); // 내부 데이터에 6바이트 넘김.

	for (unsigned int y = 0; y < Y_COUNT - 1; y++) //사각형 그리는 코드. 사각형을 옮겨서 바둑판으로 보이도록 설정함.
	{
		for (unsigned int x = 0; x < X_COUNT - 1; x++)
		{
			Rectangle(GRID_SIZE / 2 + x * GRID_SIZE, GRID_SIZE / 2 + y * GRID_SIZE, GRID_SIZE / 2 + (x + 1) * GRID_SIZE + 1,
				GRID_SIZE / 2 + (y + 1) * GRID_SIZE + 1, RGB(0, 0, 0), RGB(244, 176, 77));
		}
	}// 바둑판을 다시 그리는 일이 없도록 처음에 그림.

	ShowDisplay(); // 정보를 윈도우에 출력한다. 
	return 0;
}