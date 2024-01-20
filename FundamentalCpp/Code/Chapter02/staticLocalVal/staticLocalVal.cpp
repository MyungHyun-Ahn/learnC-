#include <iostream>

void Func1()
{
	/*
		push        ebp
		mov         ebp,esp
	*/
	static int s_Val = 1; // 여기에 해당하는 구문이 없다.
	/*
		mov         esp,ebp
		pop         ebp
		ret
	*/
}

int GetOne()
{
	return 1;
}

void Func2()
{
	static int s_Val = GetOne(); // 함수를 통해 초기화하는 경우에는 초기화 코드가 추가된다.
	/*
		mov			eax, dword ptr [$S2]
		and			eax. 1
		jne			EXIT

	START:
		mov			eax, dword ptr [$S2]
		or			ecx, 1
		mov			dword ptr [$S2], ecx
		call GetOne
		mov dword ptr [s_Val], eax

	END:
		mov			esp, ebp
		pop			ebp
		ret
	*/
}

int main()
{

	// Func1();
	Func2();

	return 0;
}