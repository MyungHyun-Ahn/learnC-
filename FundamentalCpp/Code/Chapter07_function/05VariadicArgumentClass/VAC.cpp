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


// 가변 인자로 전달될 때는 복사 생성자가 호출되지 않는다.
// 선언 자체에 각 인자들에 대한 타입이 정의되지 않았기 때문에
// 컴파일러는 오직 메모리 복사만 수행한다.
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