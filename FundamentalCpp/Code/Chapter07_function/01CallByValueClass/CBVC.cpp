#include <iostream>

using namespace std;

class CArg
{
public:
	CArg()
	{
		cout << "CArg Constructor!" << endl;
	}

	CArg(const CArg &arg)
	{
		cout << "CArg Copy Constructor!" << endl;
	}

	int m_E;			// Empty Buffer
	int m_V;
};

void Func(CArg arg)
{
	/*
	push	ebp
	mov		ebp, esp
	*/

	arg.m_V = 1;

	/*
	mov		dword ptr [ebp+0Ch], 1			; arg.m_V = 1;
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

	CArg a;
	a.m_V = 0;
	/*
	sub		esp, 8							; a ���� Ȯ��
	mov		dword ptr [ebp-4], 0			; ebp-4 ��ġ�� 0 ����
	*/

	Func(a);
	/*
	sub     esp,8							; ���� Ȯ��
	mov     ecx,esp							
	lea     eax,[a]							; eax�� a�� ��ȿ �ּ� �� ������
	push	eax								; ����� ���� �����ڿ� ��ü�� �ּ� �� ����
	call    CArg::CArg (0821451h)			; ���� ������ ȣ��
	call    Func (0821325h)					; �Լ� ȣ��
	add     esp,8
	mov		esp, ebp
	pop		ebp
	ret
	*/
}