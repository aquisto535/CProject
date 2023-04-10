#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 컴퓨터가 만든 임의의 숫자를 플레이어가 맞추는 게임
// 컴퓨터는 임의의 수를 선택하고 그 수보다 플레이어가 고른 숫자가 낮으면 low, 높으면 high로 나오도록 설정.
// 같으면 "맞았습니다"로 출력. 이 때 숫자를 몇 번에 맞췄는지 출력.

int main(void)
{
    int com; //임의 숫자
    int player; 
    int count = 0;

    srand(time(NULL)); // 임의의 숫자 결정용. 값을 받음. 항상 변하는 seed 값을 이용해서 srand를 해줌.
    // 컴퓨터는 임의의 수를 선택하고
    com = rand() % 100 + 1; //컴퓨터가 선택한 숫자는 바뀌면 안됨.

    while (1) // 맞힐 때까지 계속 루프를 돌림.
    {   
        count++; // 횟수 증가시켜줌.
        printf("숫자를 입력하세요 <1 ~ 100>\n"); 
        // 플레이어는 숫자를 입력한다.
        scanf_s("%d", &player);

        //플레이어가 선택한 숫자가 컴퓨터가 선택한 숫자보다 낮으면 High 출력
        if (player < com)
        {
            printf("High\n");
        }
        else
        {   
            //플레이어가 선택한 숫자가 컴퓨터가 선택한 숫자보다 낮으면 Low 출력
            if (player > com)
            {
                printf("Low\n");
            }
            else 
            {
                //맞췄을 때 그 동안 시도한 횟수 출력.
                printf("%d번만에 맞추셨습니다\n", count);
            }
        }
      
        
    }

    system("pause");
    return 0;
}
