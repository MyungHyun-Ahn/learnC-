#include <iostream>
#include "CFunction.h"

using namespace std;

CFunction<double(int, int)> lambda;		// Lambda Object
CFunction<double(int, int)> func;		// Function Object

double Divide(int a, int b)
{
	if (b != 0)
	{
		return (double)a / b;
	}

	return 0;
}

int main()
{
	double vx = 0.3;
	double rx = 0;

	lambda = [vx, &rx](int a, int b) -> double
		{
			rx = 0.4;
			return vx + rx + a + b;
		};

	func = &Divide;
	cout << lambda(1, 2) << endl;
	cout << func(1, 2) << endl;

	return 0;
}