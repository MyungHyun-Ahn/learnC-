#include <iostream>

using namespace std;

int main()
{
	int a = 1;
	int &ra = a;
	// ra�� �����ͷ� �����ϸ�
	// �ʱ�ȭ�� ��� &(�ּ� ������)�� �����ǰ�
	// ���� ����� ��� *(���� ������)�� �����Ǵ� ��
	/*
		lea         rax,[a]
		mov         qword ptr [ra],rax
	*/

	ra = 2;
	/*
		mov         rax,qword ptr [ra]
		mov         dword ptr [rax],2
	*/

	cout << a << endl;


	int *pa = &a;
	/*
		lea         rax,[a]
		mov         qword ptr [pa],rax
	*/

	*pa = 3;
	/*
		mov         rax,qword ptr [pa]
		mov         dword ptr [rax],3
	*/



	cout << a << endl;

	const int &ra2 = 1;
	int *pa2 = (int *)&ra2;
	*pa2 = 2;
	cout << ra2 << endl;


	/*
	���� 3
	void main() // ������� �����Ѵٰ� ����
	*/

	/*
		push ebp
		mov ebp, esp
		sub esp, 10h
	*/

	int a3 = 1;
	int &ra3 = a3;
	/*
	mov dword ptr [ebp-0Ch], 1
	lea eax, [ebp-0Ch]
	mov dword ptr [ebp-10h], eax
	*/

	const int &rc3 = 2;
	/*
	mov dword ptr [ebp-4], 2
	lea ecx, [ebp-4]
	mov dword ptr [ebp-8], ecx
	*/

	return 0;
}