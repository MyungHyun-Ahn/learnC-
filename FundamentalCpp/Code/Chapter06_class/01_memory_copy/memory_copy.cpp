/*
메모리 복사 방식
*/

int main()
{
	int x = 1;
	/*
	 mov         eax,dword ptr [x]
	 mov         dword ptr [y1],eax
	*/

	int y1(x);
	/*
	 mov         eax,dword ptr [x]
	 mov         dword ptr [y2],eax
	*/

	int y2 = x;
	/*
	 mov         eax,dword ptr [x]
	 mov         dword ptr [y3],eax
	*/

	int y3;
	y3 = x;
	/*
	 mov         eax,dword ptr [x]
	 mov         dword ptr [y3],eax
	*/

	int y4{ x };
	/*
	 mov         eax,dword ptr [x]
	 mov         dword ptr [y4],eax
	*/
	return 0;
}