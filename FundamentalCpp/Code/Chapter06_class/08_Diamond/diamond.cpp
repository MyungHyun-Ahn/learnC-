class CTop
{
public:
	int m_Top;
};

class CMiddleA : public CTop
{
public:
	int m_MiddleA;
};

class CMiddleB : public CTop
{
public:
	int m_MiddleB;
};

class CBottom : public CMiddleA, public CMiddleB
{
public:
	CBottom()
	{
		// m_Top = 10; // 모호하다며 컴파일 에러
		CMiddleA::m_Top = 10;
		m_MiddleA = 21;
		m_MiddleB = 22;
		m_Bottom = 30;
	}

	int m_Bottom;
};

int main()
{
	CBottom c;
	/*
	// 메모리 구조
	0x0095FC48  cc cc cc cc  ????
	0x0095FC4C  0a 00 00 00  .... // m_Top
	0x0095FC50  15 00 00 00  .... // m_MiddleA
	0x0095FC54  0a 00 00 00  .... // m_Top
	0x0095FC58  16 00 00 00  .... // m_MiddleB
	0x0095FC5C  1e 00 00 00  .... // m_Bottom
	0x0095FC60  cc cc cc cc  ????
	*/
	/*
	// 어떤 멤버를 사용할지 지정해서 할당
	0x00FBF768  cc cc cc cc  ????
	0x00FBF76C  0a 00 00 00  .... // CMiddleA::m_Top
	0x00FBF770  15 00 00 00  ....
	0x00FBF774  cc cc cc cc  ????
	0x00FBF778  16 00 00 00  ....
	0x00FBF77C  1e 00 00 00  ....
	0x00FBF780  cc cc cc cc  ????
	*/

	return 0;
}