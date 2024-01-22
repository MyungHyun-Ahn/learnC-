#include <iostream>

int arr[3];
int x;
int y;
static int z;

using namespace std;

int main()
{
	arr[0] = 0xAAAA;
	arr[1] = 0xBBBB;
	x = 0xCCCC;
	y = 0xEEEE;
	z = 0xFFFF;
	cout << &arr[0] << endl;
	cout << &arr[1] << endl;
	cout << x << endl;
	cout << y << endl;
	cout << z << endl;
	
}