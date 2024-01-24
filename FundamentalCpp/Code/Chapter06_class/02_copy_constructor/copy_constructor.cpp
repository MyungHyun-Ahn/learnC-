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
		// 여기서 아무 일도 하지 않기 때문에 쓰레기 값
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
	 call        CTest::CTest (0A13C5h) ; 기본 생성자
	 mov         dword ptr [t0],3
	*/

	CTest t1(t0); // 1 - 복사 생성자 호출
	t1.ShowValue(); // 쓰레기 값
	/*
	 lea         eax,[t0]
	 push        eax
	 lea         ecx,[t1]
	 call        CTest::CTest (0A115Eh) ; 복사 생성자
	*/

	CTest t2 = t0; // 2 - 복사 생성자 호출
	t1.ShowValue(); // 쓰레기 값
	/*
	 lea         eax,[t0]
	 push        eax
	 lea         ecx,[t2]
	 call        CTest::CTest (0A115Eh) ; 복사 생성자
	*/

	CTest t3; 
	/*
	 lea         ecx,[t3]
	 call        CTest::CTest (0A13C5h) ; 기본 생성자
	*/
	t3 = t0; // 3 - 실제로 객체를 먼저 생성하고 대입 연산자 호출
	/*
	 mov         eax,dword ptr [t0]
	 mov         dword ptr [t3],eax ; 대입 연산
	*/
	t3.ShowValue();

	return 0;
}