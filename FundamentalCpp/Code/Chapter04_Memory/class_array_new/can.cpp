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

// �ڽĿ��� �Ҹ��ڰ� ���� ���
// ������� �Ҹ��ڰ� �������� �ʴ´�.
// �׷��ٰ� �Ͻ����� �Ҹ��ڰ� ���� ���� �ƴϴ�.
// ���
class CChild : public CParent
{
public:
	int m_Value;
};

int main()
{
	int *mArr = (int *)malloc(sizeof(int) * 2);

	int *nArr = new int[2]; // malloc �� �����ϴ�.

	mArr[0] = 0;
	mArr[1] = 1;

	nArr[0] = 2;
	nArr[1] = 3;

	free(mArr);
	delete[] nArr;

	CTest *cTestArr = new CTest[2]; // �� 12����Ʈ(�Ҹ��ڰ� ���� ���) x86 ����
									// �Ҹ��ڰ� ���ٸ� �Ϲ� �迭�� �Ȱ��� ����� �������� �ʴ´�.
	cout << " " << endl;
	delete[] cTestArr;

	CChild *pC = new CChild[2];
	cout << *(int *)((BYTE *)pC - 4) << endl;
	delete[] pC;

}