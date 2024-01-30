#include <iostream>

using namespace std;

class CLambda
{
public:
	CLambda(int &vx, int &rx) : _vx(vx), _rx(rx) {}

	int operator()(int arg)
	{
		_rx = 10;
		return _vx + _rx + arg;
	}

	const int _vx;
	int &_rx;
};

void main()
{
	int vx = 100;
	int rx = 0;

	/*
	 push        1
	 lea         eax,[rx]
	 push        eax
	 lea         ecx,[vx]
	 push        ecx
	 lea         ecx,[ebp-110h]
	 call        `main'::`2'::<lambda_1>::<lambda_1> (0F91870h)		; Ŭ���� �����ڶ� ����� ����
	 mov         ecx,eax
	 call        `main'::`2'::<lambda_1>::operator() (0F91950h)		; operator() ȣ��
	 mov         dword ptr [R1],eax
	*/
	int R1 = [vx, &rx](int arg) -> int // ���� ĸó �κ� - Ŭ���� �������� �ʱ�ȭ ����Ʈ�� �Ȱ��� ����
		{	// operator() ������
			rx = 10;
			return vx + rx + arg;
		} (1);

	/*
	 lea         eax,[rx]
	 push        eax
	 lea         ecx,[vx]
	 push        ecx
	 lea         ecx,[lambda]
	 call        CLambda::CLambda (0FB13BBh)
	*/
	CLambda lambda(vx, rx);
	/*
	 push        1
	 lea         ecx,[lambda]
	 call        CLambda::operator() (0FB10FFh)
	 mov         dword ptr [R2],eax
	*/
	int R2 = lambda(1);

	cout << R1 << endl;
	cout << R2 << endl;
}