#include <iostream>

int main()
{
	// void*�� �޸� ����� ����Ű�� �ּҸ� ��ȯ
	// �ݵ�� ĳ������ �ؾ��Ѵ�.
	int *p1 = (int *)malloc(sizeof(int));
	*p1 = 1;

	// new�� ���������� malloc�� ȣ���Ѵ�.
	// delete ���� ���������� free�� ȣ���Ѵ�.
	// �ᱹ �߰����� ó���� �ϱ� ���� new�� delete�� ����ؾ� �ϰ�
	// malloc�� free�� ����� �� ����.
	// �߰����� ó���� �ٷ� �����ڿ� �Ҹ����̴�.
	int *p2 = new int;
	*p2 = 2;

	int *pArr1 = (int *)malloc(sizeof(int) * 2);
	pArr1[0] = 0;
	pArr1[1] = 1;

	int *pArr2 = new int[2];
	pArr2[0] = 2;
	pArr2[1] = 3;

	free(p1);
	delete p2;

	free(pArr1);
	delete[] pArr2;
}