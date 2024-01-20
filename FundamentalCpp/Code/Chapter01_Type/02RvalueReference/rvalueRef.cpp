#include <iostream>

using namespace std;

int GetValue()
{
	int a = 1;
	return a;
}

int &GetReference()
{
	int a = 2;
	return a;
}

void Func(int &arg)
{
	cout << "LValue" << endl;
}

void Func(int &&arg)
{
	cout << "RValue" << endl;
}

int main()
{
	Func(1); // Rvalue

	int a = 1;
	Func(a); // Lvalue

	Func(GetValue()); // Rvalue
	Func(GetReference()); // Lvalue

	return 0;
}