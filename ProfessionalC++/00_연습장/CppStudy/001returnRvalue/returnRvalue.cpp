#include <iostream>

int &&RvalueTest()
{
	int lvalue = 10;
	return std::move(lvalue);
}

int main()
{
	int x = RvalueTest();

	std::cout << x << std::endl;

	return 0;
}