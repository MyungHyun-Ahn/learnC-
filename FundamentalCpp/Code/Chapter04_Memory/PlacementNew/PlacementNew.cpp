#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <windows.h>

class CVSPerson
{
public:
	CVSPerson()
	{
		m_Age = 1;
		m_Name[0] = NULL;
	}

	int m_Age;
	char m_Name[1];
};

int main()
{
	const char *name = "Myung Hyun Ahn";
	void *pData = malloc(sizeof(CVSPerson) + strlen(name));

#pragma push_macro("new")
#undef new
	CVSPerson *pVSPerson = new (pData) CVSPerson;
#pragma pop_macro("new")

	strcat(pVSPerson->m_Name, name);

}