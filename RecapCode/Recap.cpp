#include <stdio.h>

unsigned char ResetBit(unsigned char dest_data, unsigned char bit_num)
{
	/* 1.0x01 << bit_num: ������ ũ�⸸ŭ 0x01�� ��Ʈ �̵���Ŵ(1����Ʈ ������ ��Ʈ �̵��� 1~7������ ������) */
	/* 2. OR ���� ���� */

	if (bit_num < 8) dest_data = dest_data  | (0x01 << bit_num); 

	//����� �� Ȯ��

	return dest_data;

}

int main()
{
	unsigned char lamp_state = 0x7F;
	printf("%X -> ", lamp_state); // ���� �� �� ��¤� 

	//lamp_state ������ 3��° ��Ʈ�� 0���� ����
	lamp_state = ResetBit(lamp_state, 3);
	printf("%X", lamp_state); // ���� �� �� ���

	return 0;
}

//16����(ǥ��) : 0xcc 1100 1100
//16����(ǥ��) : 0x30 0011 0000


