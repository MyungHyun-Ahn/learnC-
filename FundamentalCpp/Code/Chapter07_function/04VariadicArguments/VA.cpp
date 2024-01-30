#include <iostream>

using namespace std;

void Func(int vas, ...)
{
	char *arg_ptr;
	arg_ptr = (char *)&vas;
	arg_ptr += sizeof(void *);


	char a1 = *(char *)arg_ptr;
	arg_ptr += sizeof(void *);

	int a2 = *(int *)arg_ptr;
	arg_ptr += sizeof(void *);

	double a3 = *(double *)arg_ptr;
	arg_ptr += sizeof(double);

	char *a4 = *(char **)arg_ptr;
	arg_ptr += sizeof(char *);

	arg_ptr = NULL;

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