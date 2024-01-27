#include <stdio.h>

void Func(int arg)
{
	/*
	push	ebp					; 함수가 시작될 때 기본적으로 스택 프레임을 초기화 하는 구문
	mov		ebp, esp
	*/

	arg = 1;

	/*
	mov		dword ptr [ebp+8], 1	; 스택의 인자가 전달된 ebp+8 영역에 1 대입 0x00AFFB78
	pop		ebp						; pop ebp 스택의 상단에 있는 값을 ebp에 채운다.
	ret								; 이전 함수 흐름으로 돌아간다.
	*/
}

int main()
{
	/*
	push	ebp					; 함수가 시작될 때 기본적으로 스택 프레임을 초기화 하는 구문
	mov		ebp, esp
	*/
	int a = 0;
	/*
	push	ecx						; a 영역 할당
	mov		dword ptr [ebp-4], 0	; 영역에 값 대입 0x00AFFC4C
	*/
	Func(a);
	/*
	mov		eax, dword ptr [ebp-4]	; eax 영역에 값 복사
	push	eax						; 스택에 push 하여 인자 입력
	call	Func					; Func 함수 호출
	add		esp, 4					; 함수에서 사용한 스택 영역 정리
	pop		ebp
	ret
	*/
	return 0;
}