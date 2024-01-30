class CTest
{
public:
	void Func_thiscall() {}
	void __cdecl Func_cdecl() {}
	void __stdcall Func_stdcall() {}
};

int main()
{
	CTest t;

	t.Func_thiscall();
	/*
	lea		ecx, [t]				; ecx = &t
	call	CTest::Func_thiscall
	*/

	t.Func_cdecl();
	/*
	lea		eax, [t]
	push	eax						; push &t
	call	CTest::Func_cdecl
	add		esp, 4
	*/

	t.Func_stdcall();
	/*
	lea		eax, [t]
	push	eax						; push &t
	call	CTest::Func_stdcall
	*/

	return 0;
}