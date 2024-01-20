int &GetB();

int InitializeA()
{
	return GetB() + 1;
}

int g_A = InitializeA();