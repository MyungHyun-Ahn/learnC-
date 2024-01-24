class CTest1
{
public:
	CTest1()
	{
		m_Value = 3;
	}
	/*
	 push        ebp
	 mov         ebp,esp
	 sub         esp,0CCh
	 push        ebx
	 push        esi
	 push        edi
	 push        ecx
	 lea         edi,[ebp-0Ch]
	 mov         ecx,3
	 mov         eax,0CCCCCCCCh
	 rep stos    dword ptr es:[edi]
	 pop         ecx
	 mov         dword ptr [this],ecx
	 mov         ecx,offset _5EA21858_il@cpp (091C000h)
	 call        @__CheckForDebuggerJustMyCode@4 (0911325h)
		{
			m_Value = 3;
	 mov         eax,dword ptr [this]
	 mov         dword ptr [eax],3
		}
	 mov         eax,dword ptr [this]
	 pop         edi
	 pop         esi
	 pop         ebx
	 add         esp,0CCh
	 cmp         ebp,esp
	 call        __RTC_CheckEsp (091123Fh)
	 mov         esp,ebp
	 pop         ebp
	 ret
	*/

	int m_Value;
};

class CTest2
{
public:
	CTest2() : m_Value(3)
	{
	}
	/*
	 push        ebp
	 mov         ebp,esp
	 sub         esp,0CCh
	 push        ebx
	 push        esi
	 push        edi
	 push        ecx
	 lea         edi,[ebp-0Ch]
	 mov         ecx,3 ; 값을 바로 대입
	 mov         eax,0CCCCCCCCh
	 rep stos    dword ptr es:[edi]
	 pop         ecx
	 mov         dword ptr [this],ecx
	 mov         ecx,offset _5EA21858_il@cpp (091C000h)
	 call        @__CheckForDebuggerJustMyCode@4 (0911325h)
	*/

	int m_Value;
};

int main()
{
	CTest1 t1;

	CTest2 t2;

	return 0;
}