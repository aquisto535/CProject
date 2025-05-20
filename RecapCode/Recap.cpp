#include <stdio.h>

unsigned char ResetBit(unsigned char dest_data, unsigned char bit_num)
{
	/* 1.0x01 << bit_num: 지정된 크기만큼 0x01을 비트 이동시킴(1바이트 변수라서 비트 이동은 1~7까지만 가능함) */
	/* 2. OR 연산 진행 */

	if (bit_num < 8) dest_data = dest_data  | (0x01 << bit_num); 

	//변경된 값 확인

	return dest_data;

}

int main()
{
	unsigned char lamp_state = 0x7F;
	printf("%X -> ", lamp_state); // 변경 전 값 출력ㄴ 

	//lamp_state 변수의 3번째 비트를 0으로 설정
	lamp_state = ResetBit(lamp_state, 3);
	printf("%X", lamp_state); // 변경 후 값 출력

	return 0;
}

//16진수(표기) : 0xcc 1100 1100
//16진수(표기) : 0x30 0011 0000


