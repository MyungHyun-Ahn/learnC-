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

	CTest t1(t0); // ���� ������
	t1.ShowValue();

	CTest t2 = t0; // ���� ������
	t2.ShowValue();

	CTest t3;
	t3 = t0; // ���� ���� ������
	/*
	 lea         eax,[t0]
	 push        eax
	 lea         ecx,[t3]
	 call        CTest::operator= (081106Eh)
	*/
	t3.ShowValue();
}