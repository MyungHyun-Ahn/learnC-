#include <iostream>
#include <windows.h>

using namespace std;

class CTest
{
public:
	int m_int;
};

class CParent
{
public:
	~CParent() {}
};

// 자식에게 소멸자가 없는 경우
// 명시적인 소멸자가 존재하지 않는다.
// 그렇다고 암시적인 소멸자가 없는 것은 아니다.
// 상속
class CChild : public CParent
{
public:
	int m_Value;
};

int main()
{
	int *mArr = (int *)malloc(sizeof(int) * 2);

	int *nArr = new int[2]; // malloc 과 동일하다.

	mArr[0] = 0;
	mArr[1] = 1;

	nArr[0] = 2;
	nArr[1] = 3;

	free(mArr);
	delete[] nArr;

	CTest *cTestArr = new CTest[2]; // 총 12바이트(소멸자가 있을 경우) x86 기준
									// 소멸자가 없다면 일반 배열과 똑같이 사이즈를 기입하지 않는다.
	cout << " " << endl;
	delete[] cTestArr;

	CChild *pC = new CChild[2];
	cout << *(int *)((BYTE *)pC - 4) << endl;
	delete[] pC;

}