class CArg
{
public:
	int m_E;
	int m_V;
};

void Func(CArg &arg)
{
	arg.m_V = 1;
	/*
	mov         eax,dword ptr [arg]			; eax = &a
	mov         dword ptr [eax+4],1			; a.m_V = 1;
	*/
}

void main()
{
	CArg a;
	a.m_V = 0;
	/*
	mov         dword ptr [ebp-0Ch],0
	*/
	Func(a);
	/*
	lea         eax,[a]				; eax = &a
	push        eax					; 인자 전달
	call        Func (0D111BDh)		; call
	add         esp,4				; 스택 정리
	*/
}