#include <iostream>

using namespace std;

class CParent
{
public:
	int m_Parent;
};

class CChild : public CParent 
{
public:
	virtual ~CChild() {}
	int m_Child;
};

int main()
{
	CChild *pC = new CChild;

	CParent *pP1 = pC;									// ������ ���� ��ȭ�� �Ͼ
	CParent *pP2 = (CParent *)pC;						// ������ ���� ��ȭ�� �Ͼ
	CParent *pP3 = static_cast<CParent *>(pC);			// ������ ���� ��ȭ�� �Ͼ
	CParent *pP4 = reinterpret_cast<CParent *>(pC);		// �״��

	cout << "pC : " << pC << endl;
	cout << "pP1 : " << pP1 << endl;
	cout << "pP2 : " << pP2 << endl;
	cout << "pP3 : " << pP3 << endl;
	cout << "pP4 : " << pP4 << endl;


	/*
	// �޸� ����
		CChild      vfptr			---> Address of destructor
		CParent		m_Parent
		CChild		m_Child
	
	*/

	return 0;
}