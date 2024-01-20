#include <iostream>

using namespace std;

int main()
{
	int i;
	// cout << hex << i << endl; // cc cc cc cc

	int *p = new int;
	cout << hex << *p << endl; // cd cd cd cd

	cout << hex << *(p - 1) << endl; // fd fd fd fd
	cout << hex << *(p + 1) << endl; // fd fd fd fd

	delete p;
	cout << hex << *p << endl; // dd dd dd dd
}