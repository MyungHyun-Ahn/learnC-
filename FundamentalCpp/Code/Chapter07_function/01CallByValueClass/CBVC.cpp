#include <iostream>

using namespace std;

class CArg
{
public:
	CArg()
	{
		cout << "CArg Constructor!" << endl;
	}

	CArg(const CArg &arg)
	{
		cout << "CArg Copy Constructor!" << endl;
	}

	int m_E;			// Empty Buffer
	int m_V;
};

void Func(CArg arg)
{
	/*
	push	ebp
	mov		ebp, esp
	*/

	arg.m_V = 1;

	/*
	mov		dword ptr [ebp+0Ch], 1			; arg.m_V = 1;
	pop		ebp
	ret
	*/
}

void main()
{
	/*
	push	ebp
	mov		ebp, esp
	*/

	CArg a;
	a.m_V = 0;
	/*
	sub		esp, 8							; a 공간 확보
	mov		dword ptr [ebp-4], 0			; ebp-4 위치의 0 대입
	*/

	Func(a);
	/*
	sub     esp,8							; 스택 확보
	mov     ecx,esp							
	lea     eax,[a]							; eax에 a의 유효 주소 값 가져옴
	push	eax								; 명시적 복사 생성자에 객체의 주소 값 전달
	call    CArg::CArg (0821451h)			; 복사 생성자 호출
	call    Func (0821325h)					; 함수 호출
	add     esp,8
	mov		esp, ebp
	pop		ebp
	ret
	*/
}