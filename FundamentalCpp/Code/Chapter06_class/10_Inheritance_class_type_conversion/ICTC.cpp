class CParent
{
public:
	int m_Parent;
};


class CChild : public CParent
{
public:
	int m_Child;
};

int main()
{
	CChild c;
	c.m_Parent = 1;
	c.m_Child = 2;

	CParent p1 = c;									// OK
	CParent p2 = (CParent)c;						// OK
	CParent p3 = static_cast<CParent>(c);			// OK
	CParent p4 = reinterpret_cast<CParent>(c);		// Error

	CParent &rp1 = c;								// OK
	CParent &rp2 = (CParent &)c;					// OK
	CParent &rp3 = static_cast<CParent &>(c);		// OK
	CParent &rp4 = reinterpret_cast<CParent &>(c);	// OK

	CParent p;
	p.m_Parent = 1;

	CChild c1 = p;									// Error
	CChild c2 = (CChild)p;							// Error
	CChild c3 = static_cast<CChild>(p);				// Error
	CChild c4 = reinterpret_cast<CChild>(p);		// Error

	CChild &c1 = p;									// Error
	CChild &c2 = (CChild &)p;						// OK
	CChild &c3 = static_cast<CChild &>(p);			// OK
	CChild &c4 = reinterpret_cast<CChild &>(p);		// OK

	return 0;
}