#include <iostream>
#include <functional>

using namespace std;

// std::function을 사용하면 전역 변수에 람다 저장 가능
std::function<int(int)> g_Lambda;

void Func()
{
	int vx = 100;
	int rx = 10;

	g_Lambda = [vx, &rx](int arg) -> int
		{
			return vx + rx + arg;
		};
}

void main()
{
	Func();

	cout << g_Lambda(1) << endl;
}