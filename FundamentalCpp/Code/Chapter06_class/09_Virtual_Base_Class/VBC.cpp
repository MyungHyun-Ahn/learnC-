class CTop
{
public:
	CTop() {}

	int m_Top;
};

class CMiddleA : virtual public CTop
{
public:
	int m_MiddleA;
};

class CMiddleB : virtual public CTop
{
public:
	int m_MiddleB;
};

class CBottom : public CMiddleA, public CMiddleB
{
public:
	CBottom()
	{
		m_Top = 10;
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
	메모리 구조
	CBottom
	CMiddleA	vbptr A
				m_MiddleA
	CMiddleB	vbptr B
				m_MiddleB
				m_Bottom
	CTop		m_Top
	*/

	/*
	// 메모리 구조
	0x004FFA04  cc cc cc cc  ????
	0x004FFA08  48 7b 1f 00  H{.. // vbptr A
	0x004FFA0C  15 00 00 00  .... // m_MiddleA
	0x004FFA10  54 7b 1f 00  T{.. // vbptr B
	0x004FFA14  16 00 00 00  .... // m_MiddleB
	0x004FFA18  1e 00 00 00  .... // m_Bottom
	0x004FFA1C  0a 00 00 00  .... // m_Top
	0x004FFA20  cc cc cc cc  ????
	*/

	return 0;
}