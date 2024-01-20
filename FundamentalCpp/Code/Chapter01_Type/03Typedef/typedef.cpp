#include <iostream>

using namespace std;

typedef double (*PFUNCTION) (int arg1, int arg2);

double Divide(int a, int b)
{
	return (double)a / b;
}

int main()
{
	PFUNCTION f = &Divide;

	cout << f(1, 2) << endl;

	return 0;
}