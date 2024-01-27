class CTest
{
public:
	int m_E;
	int m_V;
};

CTest Func()
{
	/*
	push	ebp
	mov		ebp, esp
	*/
	CTest t;
	t.m_V = 1;
	/*
	sub		esp, 8					; 8바이트 영역 확보
	mov		dword ptr [ebp-4], 1	; t.m_V = 1
	*/

	return t;
	/*
	mov		eax, dword ptr [ebp-8]	; eax = t.m_E
	mov		edx, dword ptr [ebp-4]	; edx = t.m_V
	mov		esp, ebp
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
	Func();
	/*
	sub		esp, 8					; 반환 임시 영역 8바이트 확보
	call	Func					; 함수 호출
	mov		dword ptr [ebp-8], eax	; ebp-8에 t.m_E 값 복사
	mov		dword ptr [ebp-4], edx	; ebp-4에 t.m_V 값 복사
	mov		esp, ebp
	pop		ebp
	ret
	*/
}