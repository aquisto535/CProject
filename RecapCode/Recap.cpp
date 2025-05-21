#include <stdio.h>

unsigned char GetBit(unsigned char dest_data, unsigned char bit_num)
{
	unsigned char bit_state = 0;
	
	if (bit_num < 8)
	{
		bit_state = dest_data & (0x01 << bit_num); //Ư�� ��Ʈ�� ���� ��� ���� �ٸ� ��Ʈ�� 0���� �ʱ�ȭ
		bit_state = bit_state >> bit_num; //Ư�� ��Ʈ�� ��(0 �Ǵ� 1)�� Ȯ���ϱ� ���� �ش� ��ġ���� ���� ������ ��ġ�� ��Ʈ�� �̵�

	}

	//����� �� Ȯ��

	return bit_state;

}

int main()
{
	unsigned char lamp_state = 0x75;
	unsigned char bit_state;
	int i;

	printf("%X -> ", lamp_state); // ���� �� �� ���

	for ( i = 0; i < 8; i++)
	{
		bit_state = GetBit(lamp_state, 7-i);

		printf("%d ", bit_state);
	}

	printf("\n");

	return 0;
}

//EX) 1010 0?01 �� ���� ���� �ִ� ��� ?�� ���� �˾Ƴ��� ���
// 1. ?�� ��ġ���� 1�� AND���� �����ϰ� �������� 0���� AND �����Ͽ� �ش� ��ġ�� ��Ʈ�� ���� �����ǵ��� ����(������ ��Ʈ�� ��� 0���� ����)
// 2. ?�� ���� �˾Ƴ��� ���� ?�� ��ġ�� ����Ʈ ������ ���� ���� ���������� �̵���Ŵ 0000 000? (0000 0?00 >> 2 -> 0000 000?)


