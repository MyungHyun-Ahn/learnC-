#include <iostream>

class Rect
{
public:
	constexpr Rect(size_t width, size_t height) : mWidth(width), mHeight(height) { }
	/*

	*/
	// const Rect(size_t width, size_t height) : mWidth(width), mHeight(height) { }
	/*
00007FF61C8818F0  mov         qword ptr [rsp+18h],r8
00007FF61C8818F5  mov         qword ptr [rsp+10h],rdx
00007FF61C8818FA  mov         qword ptr [rsp+8],rcx
00007FF61C8818FF  push        rbp
00007FF61C881900  push        rdi
00007FF61C881901  sub         rsp,0E8h
00007FF61C881908  lea         rbp,[rsp+20h]
00007FF61C88190D  lea         rcx,[__5BDA88B5_constexpr@cpp (07FF61C892066h)]
00007FF61C881914  call        __CheckForDebuggerJustMyCode (07FF61C881384h)
00007FF61C881919  mov         rax,qword ptr [this]
00007FF61C881920  mov         rcx,qword ptr [width]
00007FF61C881927  mov         qword ptr [rax],rcx
00007FF61C88192A  mov         rax,qword ptr [this]
00007FF61C881931  mov         rcx,qword ptr [height]
00007FF61C881938  mov         qword ptr [rax+8],rcx
00007FF61C88193C  mov         rax,qword ptr [this]
00007FF61C881943  lea         rsp,[rbp+0C8h]
00007FF61C88194A  pop         rdi
00007FF61C88194B  pop         rbp
00007FF61C88194C  ret
	*/

	constexpr size_t getArea() const { return mWidth * mHeight; }
	/*
00007FF6CDCC1850  mov         qword ptr [rsp+8],rcx
00007FF6CDCC1855  push        rbp
00007FF6CDCC1856  push        rdi
00007FF6CDCC1857  sub         rsp,0E8h
00007FF6CDCC185E  lea         rbp,[rsp+20h]
00007FF6CDCC1863  lea         rcx,[__5BDA88B5_constexpr@cpp (07FF6CDCD2066h)]
00007FF6CDCC186A  call        __CheckForDebuggerJustMyCode (07FF6CDCC1384h)
00007FF6CDCC186F  mov         rax,qword ptr [this]
00007FF6CDCC1876  mov         rcx,qword ptr [this]
00007FF6CDCC187D  mov         rax,qword ptr [rax]
00007FF6CDCC1880  imul        rax,qword ptr [rcx+8]
00007FF6CDCC1885  lea         rsp,[rbp+0C8h]
00007FF6CDCC188C  pop         rdi
00007FF6CDCC188D  pop         rbp
00007FF6CDCC188E  ret
	*/
	// const size_t getArea() const { return mWidth * mHeight; }
	/*
00007FF61C885A90  mov         qword ptr [rsp+8],rcx
00007FF61C885A95  push        rbp
00007FF61C885A96  push        rdi
00007FF61C885A97  sub         rsp,0E8h
00007FF61C885A9E  lea         rbp,[rsp+20h]
00007FF61C885AA3  lea         rcx,[__5BDA88B5_constexpr@cpp (07FF61C892066h)]
00007FF61C885AAA  call        __CheckForDebuggerJustMyCode (07FF61C881384h)
00007FF61C885AAF  mov         rax,qword ptr [this]
00007FF61C885AB6  mov         rcx,qword ptr [this]
00007FF61C885ABD  mov         rax,qword ptr [rax]
00007FF61C885AC0  imul        rax,qword ptr [rcx+8]
00007FF61C885AC5  lea         rsp,[rbp+0C8h]
00007FF61C885ACC  pop         rdi
00007FF61C885ACD  pop         rbp
00007FF61C885ACE  ret
	*/

private:
	size_t mWidth, mHeight;
};


int main()
{
	const int x = 8;
	const int y = 2;
	constexpr int x2 = 16;
	constexpr int y2 = 2;

	std::cout << x * y << std::endl;
	std::cout << x2 * y2 << std::endl;

	// constexpr Rect r(x, y);
	// size_t myArray1 = r.getArea();

	constexpr Rect r2(x, y);
	size_t myArray2[r2.getArea()];
	
	for (int i = 0; i < r2.getArea(); i++)
	{
		myArray2[i] = i;
		std::cout << myArray2[i] << std::endl;
	}

	int arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7 ,8 ,9 };
	
}