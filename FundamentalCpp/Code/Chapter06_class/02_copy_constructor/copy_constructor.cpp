#include <iostream>

using namespace std;

class CTest
{
public:
	CTest()
	{
		m_Value = 1;
	}

	CTest(const CTest &Obj)
	{
		// ���⼭ �ƹ� �ϵ� ���� �ʱ� ������ ������ ��
	}

	void ShowValue()
	{
		cout << m_Value << endl;
	}

	int m_Value;
};

int main()
{
	CTest t0;
	t0.m_Value = 3;
	/*
	 lea         ecx,[t0]
	 call        CTest::CTest (0A13C5h) ; �⺻ ������
	 mov         dword ptr [t0],3
	*/

	CTest t1(t0); // 1 - ���� ������ ȣ��
	t1.ShowValue(); // ������ ��
	/*
	 lea         eax,[t0]
	 push        eax
	 lea         ecx,[t1]
	 call        CTest::CTest (0A115Eh) ; ���� ������
	*/

	CTest t2 = t0; // 2 - ���� ������ ȣ��
	t1.ShowValue(); // ������ ��
	/*
	 lea         eax,[t0]
	 push        eax
	 lea         ecx,[t2]
	 call        CTest::CTest (0A115Eh) ; ���� ������
	*/

	CTest t3; 
	/*
	 lea         ecx,[t3]
	 call        CTest::CTest (0A13C5h) ; �⺻ ������
	*/
	t3 = t0; // 3 - ������ ��ü�� ���� �����ϰ� ���� ������ ȣ��
	/*
	 mov         eax,dword ptr [t0]
	 mov         dword ptr [t3],eax ; ���� ����
	*/
	t3.ShowValue();

	return 0;
}