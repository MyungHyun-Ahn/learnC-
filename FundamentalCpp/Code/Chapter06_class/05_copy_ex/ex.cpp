#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

#define DEFAULT_CONSTUCTOR_EXISTS
#define COPY_CONSTUCTOR_EXISTS
#define ASSIGN_OPERATOR_EXISTS

class CParent
{
public:
	CParent()
	{
		cout << "CParent - Default Constructor!" << endl;
	}

	CParent(const CParent& obj)
	{
		cout << "CParent - Copy Constructor!" << endl;
	}

	CParent &operator=(CParent &obj)
	{
		cout << "CParent - Assign Operator!" << endl;
		return *this;
	}

	int m_PValue;
};

class CMember
{
public:
	CMember()
	{
		cout << "CMember - Default Constructor!" << endl;
	}

	CMember(const CMember &obj)
	{
		cout << "CMember - Copy Constructor!" << endl;
	}

	CMember &operator=(CMember &obj)
	{
		cout << "CMember - Assign Operator!" << endl;
		return *this;
	}

	int m_MValue;
};

class CChild : public CParent
{
public:
#ifdef DEFAULT_CONSTUCTOR_EXISTS
	CChild()
	{
		cout << "CChild - Default Constructor!" << endl;
	}
#endif

#ifdef COPY_CONSTUCTOR_EXISTS
	CChild(const CChild &obj)
	{
		cout << "CChild - Copy Constructor!" << endl;
	}
#endif

#ifdef ASSIGN_OPERATOR_EXISTS
	CChild &operator=(CChild &obj)
	{
		// *this = obk; // 이렇게 하면 무한루프
		cout << "CChild - Assign Operator!" << endl;
		return *this;
	}
#endif

	int m_CValue;
	char m_str[256];
	CMember m_Member;
	CMember m_ArrMember[1][2];
};

int main()
{
	cout << "C1 Start!" << endl;

	CChild c1;
	c1.m_PValue = 1;
	c1.m_CValue = 2;
	c1.m_Member.m_MValue = 3;
	c1.m_ArrMember[0][0].m_MValue = 4;
	c1.m_ArrMember[0][1].m_MValue = 5;

	strcpy(c1.m_str, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	cout << "C2 Start!" << endl;
	CChild c2(c1);

	cout << "C3 Start!" << endl;
	CChild c3 = c1;

	cout << "C4 Start!" << endl;
	CChild c4;
	c4 = c1;

	return 0;
}