#include <iostream>

using namespace std;

class CTest
{
public:
	void Func() {}
	void Func1() 
	{
		Func();
		cout << this << endl;
	}

	void Func2()
	{
		Func();
		cout << this << m_Value << endl; // runtime error
	}

	int m_Value;
};


int main()
{
	CTest *pT = NULL;

	pT->Func1();
	pT->Func2();

	return 0;
}