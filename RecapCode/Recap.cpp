#include <stdio.h>

unsigned char GetBit(unsigned char dest_data, unsigned char bit_num)
{
	unsigned char bit_state = 0;
	
	if (bit_num < 8)
	{
		bit_state = dest_data & (0x01 << bit_num); //특정 비트의 값을 얻기 위해 다른 비트를 0으로 초기화
		bit_state = bit_state >> bit_num; //특정 비트의 값(0 또는 1)을 확인하기 위해 해당 위치에서 가장 오른쪽 위치의 비트로 이동

	}

	//변경된 값 확인

	return bit_state;

}

int main()
{
	unsigned char lamp_state = 0x75;
	unsigned char bit_state;
	int i;

	printf("%X -> ", lamp_state); // 변경 전 값 출력

	for ( i = 0; i < 8; i++)
	{
		bit_state = GetBit(lamp_state, 7-i);

		printf("%d ", bit_state);
	}

	printf("\n");

	return 0;
}

//EX) 1010 0?01 와 같은 값이 있는 경우 ?의 값을 알아내는 방법
// 1. ?의 위치에만 1을 AND연산 진행하고 나머지를 0으로 AND 연산하여 해당 위치의 비트만 값이 유지되도록 설정(나머지 비트는 모두 0으로 설정)
// 2. ?의 값을 알아내기 위해 ?의 위치를 시프트 연산을 통해 가장 오른쪽으로 이동시킴 0000 000? (0000 0?00 >> 2 -> 0000 000?)


