//#include "pch.h"
//#include "tipsware.h"
#include "stdio.h"

// �� ���α׷��� Ư���� �޼����� ������� �ʴ´�!
//NOT_USE_MESSAGE;
//
//int main()
//{
//	ShowDisplay(); // ������ �����쿡 ����Ѵ�. 
//	return 0;
//}


int main()
{
	char data[15] = {0,0,2,0,1,1,0,0,2,1,0,2,0,0 ,0 };
	int i, x, y;

	for (int i = 0; i < 12; i++)
	{
		x = i % 5 + 1; //���� ���� �������� + 1 =>2���� �迭�� ��
		y = i / 5 + 1; //���� ���� �� + 1 =>2���� �迭�� ��

		printf("%d�� %d���� " , x, y);
		if (data[i] == 1) printf("���� ���� ���� �ֽ��ϴ�.\n");
		else if (data[i] == 2) printf("�� ���� ���� �ֽ��ϴ�.\n");
		else printf("���� ���� ���� �ʽ��ϴ�.\n");

	}

	return 0;
}