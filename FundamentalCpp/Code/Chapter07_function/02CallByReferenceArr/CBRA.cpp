#include <iostream>

using namespace std;

typedef int TARR[3];

void FuncV(TARR arg)
{
	cout << "V - arr address : " << arg << endl;
	cout << "V - &arr address : " << &arg << endl;
	cout << "V - sizeof(arr) : " << sizeof(arg) << endl;
}

void FuncR(TARR &arg)
{
	cout << "R - arr address : " << arg << endl;
	cout << "R - &arr address : " << &arg << endl;
	cout << "R - sizeof(arr) : " << sizeof(arg) << endl;
}

void main()
{
	int arr[3] = { 0 };
	cout << "M - arr address : " << arr << endl;
	cout << "M - &arr address : " << &arr << endl;
	cout << "M - sizeof(arr) : " << sizeof(arr) << endl;

	FuncV(arr);
	/*
	lea         eax,[arr]
	push        eax
	call        FuncV (0C71104h)
	add         esp,4
	*/
	FuncR(arr);
	/*
	lea         eax,[arr]
	push        eax
	call        FuncR (0C712D5h)
	add         esp,4
	*/

	/*
	// 출력 결과
	M - arr address : 010FFE28
	M - &arr address : 010FFE28
	M - sizeof(arr) : 12
	V - arr address : 010FFE28
	V - &arr address : 010FFD54
	V - sizeof(arr) : 4
	R - arr address : 010FFE28
	R - &arr address : 010FFE28
	R - sizeof(arr) : 12
	*/
}