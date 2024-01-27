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
	push        eax							; a의 주소 전달
	call        Func (0C1087h)				; 함수 Call
	add         esp,4						; 스택 인자 정리
	*/
}