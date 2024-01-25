class CParent
{
public:
	int m_Parent;
};

class CChild : virtual public CParent
{
public:
	int m_Child;
};

int main()
{
	CChild *pC = new CChild;

	CParent *pP1 = pC;									// OK
	CParent *pP2 = (CParent *)pC;						// OK
	CParent *pP3 = static_cast<CParent *>(pC);			// OK
	CParent *pP4 = reinterpret_cast<CParent *>(pC);		// OK

	CParent *pP = new CParent;
	CChild *pC1 = pP;									// Error
	CChild *pC2 = (CChild *)pP;							// Error
	CChild *pC3 = static_cast<CChild *>(pP);			// Error
	CChild *pC4 = reinterpret_cast<CChild *>(pP);		// OK

	delete pC;
	delete pP;

	/*
	// 메모리 구조

		CChild
		CChild'		vbptr	  ---> 0
					m_Child		   8 -> COarent의 Offset
		CParent		m_Parent
	
	*/
}