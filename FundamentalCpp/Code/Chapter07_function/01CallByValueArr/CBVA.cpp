typedef int TARR[1];

void Func(TARR arg)
{
	/*
	push	ebp
	mov		ebp, esp
	*/

	arg[0] = 1;
	/*
	mov		eax, dword ptr [ebp+8]	; ebp+8 ��ġ�� �ִ� �迭�� �ּҸ� eax�� ������
	mov		dword ptr [eax], 1		; eax�� ��ġ 1�� ��
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

	int arr[1] = { 0 };
	/*
	push	ecx
	mov		dword ptr [ebp-4], 0 ; ecx�� 0 ����
	*/

	Func(arr);
	/*
	lea		eax, [ebp-4]	; ��ȿ �ּ� �ε� ebp-4�� �ּ� �� �ε�
	push	eax				; �ּ� �� ���� ����
	call	Func			; call
	add		esp, 4			; ���� ����
	mov		esp, ebp
	pop		ebp
	ret
	*/
}