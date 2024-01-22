#include <iostream>

int main()
{
	// void*로 메모리 덩어리를 가리키는 주소를 반환
	// 반드시 캐스팅을 해야한다.
	int *p1 = (int *)malloc(sizeof(int));
	*p1 = 1;

	// new는 내부적으로 malloc을 호출한다.
	// delete 역시 내부적으로 free를 호출한다.
	// 결국 추가적인 처리를 하기 위해 new와 delete를 사용해야 하고
	// malloc과 free가 대신할 수 없다.
	// 추가적인 처리는 바로 생성자와 소멸자이다.
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