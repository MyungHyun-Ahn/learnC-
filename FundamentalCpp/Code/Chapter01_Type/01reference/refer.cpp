#include <iostream>

using namespace std;

int main()
{
	int a = 1;
	int &ra = a;
	// ra는 포인터로 동작하며
	// 초기화할 경우 &(주소 연산자)가 생략되고
	// 직접 사용할 경우 *(간접 연산자)가 생략되는 것
	/*
		lea         rax,[a]
		mov         qword ptr [ra],rax
	*/

	ra = 2;
	/*
		mov         rax,qword ptr [ra]
		mov         dword ptr [rax],2
	*/

	cout << a << endl;


	int *pa = &a;
	/*
		lea         rax,[a]
		mov         qword ptr [pa],rax
	*/

	*pa = 3;
	/*
		mov         rax,qword ptr [pa]
		mov         dword ptr [rax],3
	*/



	cout << a << endl;

	const int &ra2 = 1;
	int *pa2 = (int *)&ra2;
	*pa2 = 2;
	cout << ra2 << endl;


	/*
	예제 3
	void main() // 여기부터 시작한다고 보고
	*/

	/*
		push ebp
		mov ebp, esp
		sub esp, 10h
	*/

	int a3 = 1;
	int &ra3 = a3;
	/*
	mov dword ptr [ebp-0Ch], 1
	lea eax, [ebp-0Ch]
	mov dword ptr [ebp-10h], eax
	*/

	const int &rc3 = 2;
	/*
	mov dword ptr [ebp-4], 2
	lea ecx, [ebp-4]
	mov dword ptr [ebp-8], ecx
	*/

	return 0;
}