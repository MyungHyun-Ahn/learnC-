#include <iostream>

using namespace std;

class CFunctor
{
public:
	CFunctor()
	{
		m_Sum = 0;
	}

	int operator() (int arg)
	{
		m_Sum += arg;
		return m_Sum;
	}

	int m_Sum;
};

void main()
{
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	CFunctor f;
	for (int i = 0; i < 10; i++)
	{
		f(array[i]);
	}

	cout << f.m_Sum << endl;
}