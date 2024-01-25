#include "pch.h"
#include "tipsware.h"

#define X_COUNT 12
#define Y_COUNT 12

#define GRID_SIZE 30

//토글에 필요한 데이터 + 원 데이터 같이 담아둠. 이를 구현하기 위해 구조체를 사용함.
struct AppData
{
	char state[Y_COUNT][X_COUNT]; // 빈 사각형인지 아닌지 파악 정보
	char step; // 색깔 정보
};

void OnLeftBtnDown(int a_mixed_key, POINT a_pos)
{
	unsigned int x = a_pos.x / GRID_SIZE, y = a_pos.y / GRID_SIZE; // 적용 대상을 지정하기 위한 숫자.

	AppData* p_data = (AppData*)GetAppData();

	if (x < X_COUNT && y < Y_COUNT && !p_data->state[y][x]) //!p_data->state[y][x]는 다시 클릭했을 때 그려지는 현상 방지 위함임. p_data->state[y][x]이 0이라는 의미는 전까지 클릭된 적이 없다는 이야기임.
	{
		p_data->state[y][x] = p_data->step + 1; //p_data->state[y][x] = 1;

		p_data->step = !p_data->step; // p_data->state[y][x]을 조작하기 위한 변수. p_data->step = 1;

		ShowDisplay();
	} //클릭한 위치에 원만 그리도록 변경.

}


// 마우스 왼쪽 버튼만 사용
MOUSE_MESSAGE(OnLeftBtnDown, NULL, NULL)

int main()
{
	TextOut(10, 10, RGB(0, 0, 255), "사각형을 클릭하면 색상이 변경됩니다~");

	AppData data;
	memset(&data, 0, sizeof(data));

	SetAppData(&data, sizeof(data)); // 내부 데이터에 6바이트 넘김.

	ShowDisplay(); // 정보를 윈도우에 출력한다. 
	return 0;
}