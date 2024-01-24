#include <iostream>

using namespace std;

class CTest
{
public:
	CTest &operator = (const CTest &obj)
	{
		m_Value = 3;
		return *this;
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
	t0.m_Value = 5;

	CTest t1(t0); // 복사 생성자
	t1.ShowValue();

	CTest t2 = t0; // 복사 생성자
	t2.ShowValue();

	CTest t3;
	t3 = t0; // 복사 대입 연산자
	/*
	 lea         eax,[t0]
	 push        eax
	 lea         ecx,[t3]
	 call        CTest::operator= (081106Eh)
	*/
	t3.ShowValue();
}