#include <iostream>


int main()
{
	// 사용되지 않을 수도 있다는 것을 컴파일러에게 알림 C++17
	[[maybe_unused]] int cc = 0;

	int a_;

	int a = 0;
	int b{};
	int c{ 0 };

	int d{ 3 };
	int e = { 3 };
	int f(3);
	int g = (3);

	a_ = 0;
	
	std::cout << a << b << c << d << e << f << g << std::endl;
}