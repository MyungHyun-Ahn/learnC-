void Func(int &arg)
{
	arg = 1;
	/*
	mov         eax,dword ptr [arg]			; eax = &a
	mov         dword ptr [eax],1			; a = 1
	*/
}

void main()
{
	int a = 0;
	/*
	mov         dword ptr [a],0
	*/
	Func(a);
	/*
	lea         eax,[a]						; eax = &a
	push        eax							; a�� �ּ� ����
	call        Func (0C1087h)				; �Լ� Call
	add         esp,4						; ���� ���� ����
	*/
}