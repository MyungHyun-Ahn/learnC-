#include <iostream>

using namespace std;

class CTest
{
public:
	CTest()
	{
		m_Value = 1;
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

	CTest t1(t0);
	/*
	 mov         eax,dword ptr [t0]
	 mov         dword ptr [t1],eax
	*/
	t1.ShowValue(); // 3 출력

	CTest t2 = t0;
	/*
	 mov         eax,dword ptr [t0]
	 mov         dword ptr [t2],eax
	*/
	t1.ShowValue(); // 3 출력

	CTest t3;
	/*
	 lea         ecx,[t3]
	 call        CTest::CTest (0A313C0h)
	*/
	t3 = t0;
	/*
	 mov         eax,dword ptr [t0]
	 mov         dword ptr [t3],eax
	*/

	t3.ShowValue(); // 3 출력

	return 0;
}