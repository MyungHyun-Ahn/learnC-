#include <stdio.h>

void Func(int arg)
{
	/*
	push	ebp					; �Լ��� ���۵� �� �⺻������ ���� �������� �ʱ�ȭ �ϴ� ����
	mov		ebp, esp
	*/

	arg = 1;

	/*
	mov		dword ptr [ebp+8], 1	; ������ ���ڰ� ���޵� ebp+8 ������ 1 ���� 0x00AFFB78
	pop		ebp						; pop ebp ������ ��ܿ� �ִ� ���� ebp�� ä���.
	ret								; ���� �Լ� �帧���� ���ư���.
	*/
}

int main()
{
	/*
	push	ebp					; �Լ��� ���۵� �� �⺻������ ���� �������� �ʱ�ȭ �ϴ� ����
	mov		ebp, esp
	*/
	int a = 0;
	/*
	push	ecx						; a ���� �Ҵ�
	mov		dword ptr [ebp-4], 0	; ������ �� ���� 0x00AFFC4C
	*/
	Func(a);
	/*
	mov		eax, dword ptr [ebp-4]	; eax ������ �� ����
	push	eax						; ���ÿ� push �Ͽ� ���� �Է�
	call	Func					; Func �Լ� ȣ��
	add		esp, 4					; �Լ����� ����� ���� ���� ����
	pop		ebp
	ret
	*/
	return 0;
}