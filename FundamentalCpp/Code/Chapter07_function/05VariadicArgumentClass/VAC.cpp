#include <iostream>
#include <stdarg.h>

using namespace std;

class CTest
{
public:
	CTest()
	{
		m_V = 0;
	}

	CTest(const CTest &obj)
	{
		m_V = obj.m_V + 1;
	}

	int m_V;
};

void CFunc(CTest arg)
{
	CTest t = arg;
	cout << "CFunc : " << t.m_V << endl;
}


// ���� ���ڷ� ���޵� ���� ���� �����ڰ� ȣ����� �ʴ´�.
// ���� ��ü�� �� ���ڵ鿡 ���� Ÿ���� ���ǵ��� �ʾұ� ������
// �����Ϸ��� ���� �޸� ���縸 �����Ѵ�.
void VAFunc(int vas, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, vas);
	CTest t = va_arg(arg_ptr, CTest);
	va_end(arg_ptr);

	cout << "VAFunc : " << t.m_V << endl;
}

int main()
{
	CTest t;

	CFunc(t);
	VAFunc(0, t);

	return 0;
}