
#include <iostream>
#include <stdarg.h>

using namespace std;

void Func(int vas, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, vas);
	char a1 = va_arg(arg_ptr, char);
	int a2 = va_arg(arg_ptr, int);
	double a3 = va_arg(arg_ptr, double);
	char* a4 = va_arg(arg_ptr, char *);
	va_end(arg_ptr);

	cout << a1 << a2 << a3 << a4 << endl;
}

int main()
{
	char a1 = '1';
	int a2 = 2;
	double a3 = 3.0;
	const char *a4 = "four";
	Func(0, a1, a2, a3, a4);

	return 0;
}