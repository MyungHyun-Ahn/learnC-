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
	sub		esp, 8					; 8����Ʈ ���� Ȯ��
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
	sub		esp, 8					; ��ȯ �ӽ� ���� 8����Ʈ Ȯ��
	call	Func					; �Լ� ȣ��
	mov		dword ptr [ebp-8], eax	; ebp-8�� t.m_E �� ����
	mov		dword ptr [ebp-4], edx	; ebp-4�� t.m_V �� ����
	mov		esp, ebp
	pop		ebp
	ret
	*/
}