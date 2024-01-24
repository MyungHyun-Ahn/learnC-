#include <iostream>

class CParentA
{
public:
	CParentA()
	{
		m_AVal = 1;
		m_AVal2 = 1;
	}

	int GetAVal()
	{
		return m_AVal;
		/*
		 mov         eax,dword ptr [this]
		 mov         eax,dword ptr [eax]
		*/
	}

	int m_AVal;
	int m_AVal2;
};

class CParentB
{
public:
	CParentB()
	{
		m_BVal = 2;
	}

	int GetBVal()
	{
		return m_BVal;
		/*
		 mov         eax,dword ptr [this]
		 mov         eax,dword ptr [eax]
		*/
	}

	int m_BVal;
};

class CChild : public CParentA, public CParentB
{
public:
	CChild()
	{
		m_CVal = 3;
	}

	int GetCVal()
	{
		return m_CVal;
		/*
		 mov         eax,dword ptr [this]
		 mov         eax,dword ptr [eax+0Ch] ; ������ ����� �� this���� + 0Ch ��ġ�� ���� ������
		*/
	}

	int m_CVal;
};

int main()
{
	CChild c;
	/*
	 lea         ecx,[c]
	 call        CChild::CChild (0C21384h)
	*/

	CParentA *pA = &c;
	/*
	 lea         eax,[c]
	 test        eax,eax
	 je          __$EncStackInitStart+46h (0C22B92h)
	 lea         ecx,[c]
	 add         ecx,8
	 mov         dword ptr [ebp-128h],ecx
	 jmp         __$EncStackInitStart+50h (0C22B9Ch)
	 mov         dword ptr [ebp-128h],0
	 mov         edx,dword ptr [ebp-128h]
	 mov         dword ptr [pB],edx
	*/

	CParentB *pB = &c;
	/*
	 lea         eax,[c]
	 test        eax,eax
	 je          __$EncStackInitStart+46h (0C22B92h)
	 lea         ecx,[c]
	 add         ecx,8 ; �������� �����Ϸ��� ����Ͽ� �ٲ���
	 mov         dword ptr [ebp-128h],ecx
	 jmp         __$EncStackInitStart+50h (0C22B9Ch)
	 mov         dword ptr [ebp-128h],0
	 mov         edx,dword ptr [ebp-128h]
	 mov         dword ptr [pB],edx
	*/

	CChild *pC = &c;
	/*
	 lea         eax,[c]
	 mov         dword ptr [pC],eax
	*/

	int Ret1 = pA->GetAVal();
	/*
	 mov         ecx,dword ptr [pC]
	 add         ecx,8 ; �ƿ� ȣ������ this ������ ������ ����� �ؼ� �ѱ��.
	*/
	int Ret2 = pC->GetBVal();
	int Ret3 = pC->GetCVal();

	std::cout << "pA : " << pA << "\n\0";
	std::cout << "pB : " << pB << "\n\0";
	std::cout << "pC : " << pC << "\n\0";

	return 0;
}