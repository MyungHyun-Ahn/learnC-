# Chapter 07 함수

## 7.1 함수 타입
C/C++에서 타입 or 형이란 단어는 결코 낯설지 않다.
* C++의 모든 객체가 타입을 가진다.
* 그러나 객체만 타입을 가지는 것이 아니다.

함수도 타입을 가진다.
* 바로 시그니처

함수 시그니처
* 함수 인자들의 타입과 순서, 그리고 반환 타입
* 추가로 함수 호출 규약, 클래스 타입
* 그외에 함수 이름 자체를 포함시키는 경우도 있다.

가장 일반적으로 많이 사용되는 시그니처의 정의
* 인자의 타입 및 순서, 반환 타입, 클래스 타입 및 const, 함수 호출 규약을 포함

함수의 타입이란 곧 함수의 시그니처이다.


## 7.2 함수 호출 규약 (Calling Convention)
함수 호출 규약은 보통 컴퓨터 구조나 어셈블리를 공부할 때 주로 배운다.
* C/C++에 종속된 개념은 아니다.
* C/C++의 기초적인 원리를 제대로 이해하기 위해 필요하다.

### 7.2.1 cdecl
기본 함수 호출 x86 어셈블리
~~~c++
int Plus(int a, int b);


void main()
{
    /*
        push    ebp
        mov     ebp, esp
        push    ecx
    */

    int Sum = Plus(1, 2);
    /*
        push    2
        push    1
        call    Plus
        add     esp, 8
        mov     dword ptr [ebp-4], eax
    */
}

int Plus(int a, int b)
{
    return a + b;
    /*
        push    ebp
        mov     ebp, esp
        mov     eax, dword ptr [ebp+8]
        add     eax, dword ptr [ebp+0Ch]
        pop     ebp
        ret
    */
}
~~~

어셈블리를 분석하기 위해서 먼저 스레드 스택에 대해서 알고 있어야 한다.
* 스레드 스택 : 스레드마다 생성되는 메모리 영역
* LIFO 방식으로 입출력이 되기 때문에 보통 스레드 스택이라고 부른다.

스택에서 꼭 알아야할 개념
* esp 레지스터 : 스택에서 현재 위치를 나타내는 지시자
* push, pop 명령어 : 스택에 입출력을 담당하는 명령어

스택에 삽입을 많이 하면 스택의 크기가 커지고 삭제를 많이 하면 스택의 크기가 작아진다.
* 보통 스택이 커지는 것을 스택이 자란다. 라고 표현한다.
* 스택은 메모리 주소가 작은 쪽에서 큰 쪽, 큰 쪽에서 작은 쪽으로 자랄 수도 있다.
* 대부분의 컴파일러는 주소가 큰 쪽에서 작은 쪽으로 스택이 자라도록 설계한다. (VC++, GCC도 마찬가지)


스택의 기본 동작

~~~
Low                           

                    -> push 1                -> push 2      <-- esp  -> pop ebp
                                    <-- esp              2                          2  <-- esp
High      <-- esp               1                        1                          1
~~~
* 아래쪽일수록 메모리 주소가 큰 것을 의미
* esp는 스택에서 기준점을 나타낸다.
* esp를 기준으로 push와 pop이 일어난다.
* pop ebp : ebp 레지스터에 스택의 상단 값을 가져오면서 스택의 크기를 줄이겠다는 의미

기본 함수 호출의 스레드 스택 변화
~~~
LOW                                                                  <- esp
                                                                 1 
                                                     <- esp      2
                                <- esp, ebp     eax  <- ebp     ecx  <- ebp
HIGH       <-- esp         ebp                  ebp             ebp
~~~
~~~
LOW                        <- esp, ebp
          <- esp  main ebp                     <- esp
    복귀주소        복귀주소             복귀주소                   <- esp
       1              1                   1                   1
       2              2                   2                   2
      ecx <- ebp     ecx                 ecx   <- ebp        ecx <- ebp
HIGH  ebp            ebp                 ebp                 ebp
~~~
~~~
LOW
           <- esp       <- ebp-4
       ecx <- ebp    3  <- ebp
HIGH   ebp          ebp
~~~

ebp 레지스터는 고정된 기준점을 의미한다.
* esp는 push나 pop을 수행될 때마다 변화한다.
* 따라서 특정한 위치를 esp를 기준으로 가리키는 것은 불가하다.
* 그래서 고정된 위치를 가리키는 ebp 레지스터가 필요하며
* 함수가 처음 시작하는 순간에 현재 스택의 위치를 나타내는 esp를 ebp에 대입한 이후
* 함수 안에서는 ebp를 기준으로 특정 위치에 접근할 수 있는 것이다.

ebp를 esp를 대입하기 전에 push ebp를 하는 것
* 이전에 설정된 ebp를 먼저 스택에 저장하고 지금 함수의 esp로 갱신하겠다는 의미

이전의 ebp라는 것은 바로 현재 함수를 호출한 함수의 ebp이다.
* 즉, 함수가 종료된 이후에는 다시 ebp를 복원해야하기 때문에 저장해둔다.

push ecx를 수행한다. - 스택이 자라났다.
* int Sum을 위한 영역이다.
* 지역 객체의 특징은 함수가 시작될 때 스택에 잠깐 생성되고
* 반환된 이후에는 스택에서 사라져 접근 자체가 무의미해진다.
* 결국 ecx가 차지하는 영역에 함수 반환 결과가 저장될 것이다.

Plus가 호출된다.
* 먼저 인자 1, 2를 스택에 입력한다.
* 어셈블리에서는 2, 1 순으로 역순으로 입력한다. - 함수 호출 규약의 특성 (오른쪽에서 왼쪽으로 인자를 입력)

call Plus
* call이 호출되면 스레드의 실행 흐름은 Plus가 정의된 메모리 영역으로 넘어가서 실행된다.

실행 흐름을 변경하는 어셈블리 명령어
* jmp, je, jne

call은 일반적인 점프에 비해서 다른 것이 있다.
* 복귀 주소를 스택에 입력한다는 것
* call은 함수가 반환된 이후에 실행되어야 하는 복귀 주소를 스택에 입력한다.

Plus 함수 실행
* push ebp : 이전 함수의 ebp를 스택에 저장
* ebp를 새롭게 갱신
* 여기서 ebp에 저장한 것은 main의 ebp

mov dword ptr [ebp+8], eax
* ebp+8이 가리키는 영역의 값을 읽어서 eax에 대입
* ebp+8을 한다는 것은 ebp를 아래로 2칸 이동시킨다는 것이다.
* 즉, 1을 가져오게 된다.

add eax, dword ptr [ebp+0Ch]
* 0Ch는 10진수로 12 즉, 3칸 이동한 값을 eax에 더하라
* eax + 2를 수행하라는 것이다.
* 즉, eax의 값은 3이 된다.

스택의 특정한 위치를 접근할 때 ebp가 사용된다.
* esp를 사용할 수도 있는데 조금만 복잡해지면 이해하기 어려워진다.
* 따라서 대부분의 컴파일러는 ebp를 사용한다.


결과를 eax에 대입했으니 함수가 할 일은 끝이 났다.
* 함수 호출 이전으로 돌아가면 된다.

pop ebp
* 스택의 맨 위에는 이전 함수 즉, main ebp가 들어있다.
* 따라서 ebp는 main의 것으로 되돌려진다.

ret
* 복귀 주소로 돌아가라는 명령이다.
* ret이 하는 동작은 esp가 가리키는 메모리 영역을 pop 하면서
* 복귀 주소를 구해내고 그곳으로 점프하는 것이다.

add esp, 8
* 스택을 정리한다.
* 이전 함수에서 사용한 스택을 정리한다.
* pop을 2번하는 것보다 효율적이다.

mov dword ptr [ebp-4], eax
* eax의 값을 ebp-4에 대입하라
* 함수의 반환 값을 가져오는 것이다.


위 과정에서 정형화된 부분이 함수 호출 규약이다.
1. 함수의 인자들이 역순으로 스택에 입력되어 전달된다.
2. 일반적으로 함수의 반환 값은 eax 레지스터에 대입된다는 것
3. 함수가 반환된 이후 사용되지 않는 인자의 스택 영역을 호출한 함수가 정리한다는 것

원래 함수를 선언 및 정의할 때는 함수 호출 규약을 지정해주어야 한다.
* 보통 컴파일러의 기본값이 cdecl이기 때문에 Plus 함수는 cdecl

VC++에서는 stdcall과 fastcall으로 변경할 수 있다.
* 안하는 것이 좋다.

### 7.2.2 stdcall
~~~c++
int Plus(int a, int b);


void main()
{
    /*
        push    ebp
        mov     ebp, esp
        push    ecx
    */

    int Sum = Plus(1, 2);
    /*
        push    2
        push    1
        call    Plus
        mov     dword ptr [ebp-4], eax
    */
}

int Plus(int a, int b)
{
    return a + b;
    /*
        push    ebp
        mov     ebp, esp
        mov     eax, dword ptr [ebp+8]
        add     eax, dword ptr [ebp+0Ch]
        pop     ebp
        ret     8
    */
}
~~~

ret 8
* esp가 가리키는 주소를 pop 하면서 esp에 다시 한 번 8을 더하고 점프하라는 의미
* 즉, esp를 두 칸 아래로 내리는 동작이 추가된 것

stdcall을 정리해보자.
1. cdecl과 마찬가지로 인자를 오른쪽에서 왼쪽으로 스택에 입력
2. 결과 또한 마찬가지로 eax에 대입하여 반환
3. 인자의 스택 영역을 호출된 함수가 정리

cdecl과 가장 큰 차이점은
* 전달된 인자의 스택 영역을 누가 정리하느냐이다.

main 처럼 다른 함수를 호출하는 주체를 caller\
Plus처럼 호출된 함수를 callee라고 부른다.


마지막 정리
* cdecl은 caller가 스택 영역을 정리하고, stdcall은 callee가 스택 영역을 정리한다.


왜 함수 호출 규약이 여러 개 존재할까?
* cdecl 방식은 가변 인자 함수를 가능하게 할 수 있다. ex printf
* stdcall 방식으로는 절대 가변 인자 함수를 만들 수 없다.
* stdcall의 장점은 바이너리 코드의 양을 줄일 수 있다.
* 객관적으로 cdecl이 가변 인자 함수를 만들 수 있다는 장점 때문에 우위에 있다.


32비트 x86 시스템에서는 cdecl, stdcall, fastcall, thiscall 등등이 사용되지만

64비트 x64 시스템에서는 통일된 호출 규약이 사용된다.


### 7.2.3 x64 Calling Convention
64비트 x64 시스템에 들어서면서 드디어 함수 호출 규약은 통일되었다.
* 분석이 어려워지는 면은 있다.

기본적으로 스택 정리의 주체는 cdecl 처럼 caller
* 가변 함수도 지원해야 하기 때문에

fastcall의 특징도 포함되어 있다.
* 전달 시 일부 인자는 레지스터를 이용

참고로 통합의 의미는 cdecl, stdcall, fastcall, thiscall 등이 통합되었다는 의미다.
* x64 함수 호출 규약은 컴파일러마다 조금씩 다를 수 있다.

기본 함수 호출(x64 Calling Convention)
~~~c++
int Plus(int a, int b);


void main()
{
    int Sum = Plus(1, 2);
    /*
        sub     rsp, 38h
        mov     edx, 2
        mov     ecx, 1
        call    Plus
        mov     dword ptr [rsp+20h], eax
        add     rsp, 38h
    */
}

int Plus(int a, int b)
{
    return a + b;
    /*
        mov     dword ptr [rsp+10h], edx
        mov     dword ptr [rsp+8], ecx
        mov     eax, dword ptr [rsp+10h]
        mov     ecx, dword ptr [rsp+8]
        add     ecx, eax
        mov     eax, ecx
        ret
    */
}
~~~

x86에서는 32비트 esp, eax, ecx 등을 사용했는데\
x64에서는 64비트 rsp, rax, rcx 등을 사용한다.
* 일반적으로 레지스터 이름 앞에 e가 붙으면 32비트고, r이 붙으면 64비트다.
* 단, r8d, r9d 같은 예외도 있다.
* x64에서는 스택의 한 칸 크기가 8바이트이다.

x64에서는 ebp를 사용하지 않고 rsp로만 스택에 접근한다.
* 분석이 어려워진다.

~~~
Low                                              <- rsp             <- rsp
                            <- rsp      복귀 주소            복귀 주소
                                                               1
                                                               2





High       <- rsp
~~~
~~~
Low  
          <- rsp         <- rsp     
       1              1
       2              2


                      3


High                                        <- rsp
~~~

main이 시작된다. sub rsp, 38h
* 38h : 10진수로 56
* 즉, rsp를 7칸 위로 올리라는 뜻

x86에서는 인자를 스택에 push 했는데 x64에서는 ecx, edx 레지스터에 대입한다.
* 스택에 입력되는 과정이 사라지므로 성능 향상
* VC++의 경우 정수 인자 4개까지는 rcx, rdx, r8, r9 사용
* 5번째 인자부터는 스택에 입력을 한다.

ecx와 rcx는 각기 같은 레지스터를 가리키고 있는 것이다.
* 64비트 rcx의 하위 32비트를 ecx 레지스터라고 취급하는 것이다.
* 부동소수점 인자가 사용될 경우 xmm0, xmm1, xmm2, xmm3 4개의 레지스터가 사용된다.

call Plus
* rsp에 8을 빼서 한 칸 위로 올리고, 그 위치에 복귀 주소를 입력한다.
* x64 함수 호출 규약에서는 함수 호출 시 레지스터를 이용하여 전달되는 4개의 인자가 스택에 저장되도록
* 미리 복귀 주소 아래 4칸을 예약한다.

왜 공간을 마련해두었을까?
* 함수 안에서 함수를 또 호출할 수 있기 때문에
* 만일 전달된 인자가 스택에 저장되지 않고 다른 함수가 호출되면
* 다른 함수의 인자가 레지스터에 대입되고 기존 인자들은 사라지게 되기 때문이다.

레지스터로 넘어온 인자를 각각 예약된 스택 영역에 넣는다.
* push를 사용하지 않고 mov를 사용하므로 rsp는 변화가 없다.

인자를 더해서 결과를 만든다.
* add ecx, eax

ret이 수행된다.
* rsp가 가리키는 위치에서 pop을 수행하고 구해진 복귀 주소로 점프한다.
* x64의 pop은 rsp가 가리키는 메모리 영역의 8 바이트 값을 읽어오고
* rsp에 8을 더해서 rsp의 위치를 한 칸 내리게된다.

함수의 반환 값인 eax를 rsp+20h가 가리키는 스택의 영역에 대입한다.
* mov dword ptr [rsp+20h], eax

마지막으로 main이 종료되는 순간
* add rsp, 38h가 수행된다.
* main에서 할당했던 스택을 정리하는 코드다.

## 7.3 Name Mangling (Name Decoration)
이름을 변경한다. 꾸민다.
* 중요한 핵심 정보를 담기 위해 이름을 변경한다.

### 7.3.1 Name Mangling 포함 정보

~~~c++
int Func()
{
    return 0;
}

int Func(int arg)
{
    return arg;
}

void main()
{
    Func();
    Func(1);
}
~~~

아무 문제 없는 코드이지만, C 컴파일로 컴파일하면 에러가 발생한다.

C++은 C를 기반으로 여러가지 개념 및 문법을 새롭게 도입한 언어다.
* 함수에 있어서 결정적인 변화는 중복정의를 사용할 수 있게된 것이다.


중복정의가 없던 시절의 C 컴파일러는 예제 코드와 같은 중복정의를 할 수 없으므로 에러처리를 하는 것이다.

C++의 Name Mangling은 컴파일러가 각 함수를 구분하기 위하여 이름을 약간 변형하는 것이다.
* 새로운 함수가 오더라도 함수명이 절대로 중복되지 않도록 함수의 이름을 약간씩 변형한다.
* C++는 인자들의 개수와 타입이 다를 경우 다른 함수로 취급하게 된다.

왜 반환 타입은 중복정의의 요건으로 들어가지 않는가?
* 함수를 호출할 경우 꼭 반환 결과를 받아야만 하는 것은 아니기 때문

### 7.3.2 C 컴파일러 Name Mangling
C 컴파일러도 함수 이름에 장식을 한다.
* 중복정의를 위한 것은 아니다.

~~~c++
                                    // Name Mangling 결과
void Func1();                       // _Func1
void Func2(int arg);                // _Func2
void Func3();                       // _Func3
void Func4(double arg);             // _Func4

void __stdcall Func5();             // _Func5@0
void __stdcall Func6(int arg);      // _Func6@4
void __stdcall Func7();             // _Func7@0
void __stdcall Func8(double arg);   // _Func8@8
~~~
* 공통적으로 함수 이름 앞에 _rk qnxsmsek.
* 끝에 붙는 숫자의 의미는 실제 인자들의 타입 크기를 더한 것이다.

C 컴파일러도 Name Mangling을 통해서 함수 이름을 약간 변형하긴 한다.
* 특별히 부가 정보가 없으면 안할수도 있다.

### 7.3.3 C++ 컴파일러 Name Mangling

~~~c++
                                            // Name Mangling 결과                            
int  Func1() { return 0; }                  // ?Func1@@YAHXZ
void Func2() {}                             // ?Func2@@YAXXZ
void Func3(int arg1) {}                     // ?Func3@@YAXH@Z
void Func4(int arg1, int arg2) {}           // ?Func4@@YAXHH@Z
void Func5(double arg1) {}                  // ?Func5@@YAXN@Z
void Func6(double arg1, double arg2) {}     // ?Func6@@YAXNN@Z
void Func7(int arg1, double arg2) {}        // ?Func7@@YAXHN@Z
void Func8(double arg1, int arg2) {}        // ?Func5@@YAXNH@Z
~~~

* 대략적으로 X는 void, int는 H, double은 N을 나타낸다.
* Z로 끝나는 경우 Procedure, @Z는 Function 이라는 의미이다.
* 특별히 구분하지는 않지만 인자의 유무 차이다.
* @@ 뒤의 YA는 cdecl, YG는 stdcall을 나타낸다.


### 7.3.4 extern "C"
* extern "C"는 Name Mangling을 할 때 C 방식으로 하라는 의미다.
* 기본적으로 C++ 에는 extern "C++"이 자동으로 지정된다.
* extern은 링크의 범위를 설정하는 키워드이다.

extern "C"를 사용하는 경우는 C 파일과 CPP 파일이 혼재되어 있는 경우에 사용된다.


## 7.4 인자(Parameter / Argument)
* parameter : 함수를 선언하거나 정의할 때 사용하는 인자
* argument : 실제로 함수를 호출할 때 넘어가는 인자

### 7.4.1 인자의 전달
x86에서는 공통적으로 인자를 스택에 push하고, 함수 본체에서는 스택에 접근하여 필요한 인자를 사용하였다.\
x64 시스템에서는 가능하면 레지스터를 이용하여 인자를 전달하기도 하지만, 재귀호출을 비롯한 함수에서 함수를 호출하는 경우에는 인자를 스택에 임시적으로 저장해야만 한다.
* 결국 인자는 스택에 저장되고 함수 본체에서 스택을 통해서 인자가 사용되는 흐름이 일반적이라고 할 수 있다.

C 컴파일러에서는 함수의 인자를 더 많이 적어도 컴파일된다.
* C 형식의 cdecl 규약의 함수는 그 자체가 가변인자 함수일 수 있다는 의미

### 7.4.2 값에 의한 호출 (Call by Value)
값에 의한 호출은 말 그대로 값을 인자로 넘기는 것을 의미한다.
* 가장 중요한 것은 인자로 넘어가는 값에 대해서 스택에 인자에 대한 공간이 확보되고 값이 복사된다는 것이다.
* 매개변수(parameter)는 곧 스택에 전달된 인자가 차지하는 메모리 영역을 나타낸다.

값에 의한 호출 1 - 기본 타입
~~~C++
void Func(int arg)
{
	/*
	push	ebp					; 함수가 시작될 때 기본적으로 스택 프레임을 초기화 하는 구문
	mov		ebp, esp
	*/

	arg = 1;

	/*
	mov		dword ptr [ebp+8], 1	; 스택의 인자가 전달된 ebp+8 영역에 1 대입 0x00AFFB78
	pop		ebp						; pop ebp 스택의 상단에 있는 값을 ebp에 채운다.
	ret								; 이전 함수 흐름으로 돌아간다.
	*/
}

int main()
{
	/*
	push	ebp					; 함수가 시작될 때 기본적으로 스택 프레임을 초기화 하는 구문
	mov		ebp, esp
	*/
	int a = 0;
	/*
	push	ecx						; a 영역 할당
	mov		dword ptr [ebp-4], 0	; 영역에 값 대입 0x00AFFC4C
	*/
	Func(a);
	/*
	mov		eax, dword ptr [ebp-4]	; eax 영역에 값 복사
	push	eax						; 스택에 push 하여 인자 입력
	call	Func					; Func 함수 호출
	add		esp, 4					; 함수에서 사용한 스택 영역 정리
	pop		ebp
	ret
	*/
	return 0;
}
~~~
* 인자의 원본과 전달된 인자는 영역 자체가 다르다.
* 기본 타입인 char, int, float, double 등은 스택에 값 자체가 직접 입력되는 방식으로 쉽게 전달될 수 있다.


배열의 경우에는 예상과 다르게 동작한다.
~~~c++
typedef int TARR[1];

void Func(TARR arg)
{
	/*
	push	ebp
	mov		ebp, esp
	*/

	arg[0] = 1;
	/*
	mov		eax, dword ptr [ebp+8]	; ebp+8 위치에 있는 배열의 주소를 eax에 가져옴
	mov		dword ptr [eax], 1		; eax의 위치 1을 씀
	pop		ebp
	ret
	*/
}

void main()
{
	/*
	push	ebp
	mov		ebp, esp
	*/

	int arr[1] = { 0 };
	/*
	push	ecx
	mov		dword ptr [ebp-4], 0 ; ecx에 0 대입
	*/

	Func(arr);
	/*
	lea		eax, [ebp-4]	; 유효 주소 로드 ebp-4의 주소 값 로드
	push	eax				; 주소 값 인자 전달
	call	Func			; call
	add		esp, 4			; 스택 정리
	mov		esp, ebp
	pop		ebp
	ret
	*/
}
~~~
* 중요한 것은 int 객체를 인자로 넘길 경우 함수 호출 후에도 int 객체 값의 변화가 없지만
* 배열 객체를 인자로 넘길 경우 함수 호출 후에도 배열 요소 값의 변화가 유지된다는 것이다.
* 즉, 배열을 인자로 넘길 경우 주소가 전달되는 것


그냥 배열을 줄줄이 넘기면 안될까?
* 스택 오버 플로우가 발생한다.
* 기본적으로 스레드 당 스택의 크기는 1MB~4MB 정도밖에 되지 않는다.
* 그뿐만 아니라 크기가 큰 배열의 경우 요소의 타입에 따라 초기화에 큰 비용이 들 수 있다.


클래스(구조체 포함) 객체를 값으로서 인자를 넘기는 경우
* 클래스는 기본 타입과 마찬가지로 순수하게 포인터가 아닌 객체 자체를 인자로 넘긴다.

~~~c++
class CArg
{
public:
	int m_E;			// Empty Buffer
	int m_V;
};

void Func(CArg arg)
{
	/*
	push	ebp
	mov		ebp, esp
	*/

	arg.m_V = 1;

	/*
	mov		dword ptr [ebp+0Ch], 1			; arg.m_V = 1;
	pop		ebp
	ret
	*/
}

void main()
{
	/*
	push	ebp
	mov		ebp, esp
	*/

	CArg a;
	a.m_V = 0;
	/*
	sub		esp, 8							; a 공간 확보
	mov		dword ptr [ebp-4], 0			; ebp-4 위치의 0 대입
	*/

	Func(a);
	/*
	mov		eax, dword ptr [ebp-4]			; a.m_V 복사
	push	eax
	mov		ecx, dword ptr [ebp-8]			; a.m_E 복사
	push	ecx
	call	Func
	add		esp, 8							; 스택 정리
	mov		esp, ebp
	pop		ebp
	ret
	*/
}
~~~
* 클래스 객체가 복사되어서 인자로 넘어간다.


생성자가 존재하는 경우에는 어떻게 될까?
* 그냥 복사된다.
* 그러나 이것 또한 암시적 복사 생성자가 존재하기 때문에 그렇게 보이는 것이다.

복사 생성자가 존재하는 경우
~~~C++
#include <iostream>

using namespace std;

class CArg
{
public:
	CArg()
	{
		cout << "CArg Constructor!" << endl;
	}

	CArg(const CArg &arg)
	{
		cout << "CArg Copy Constructor!" << endl;
	}

	int m_E;			// Empty Buffer
	int m_V;
};

void Func(CArg arg)
{
	/*
	push	ebp
	mov		ebp, esp
	*/

	arg.m_V = 1;

	/*
	mov		dword ptr [ebp+0Ch], 1			; arg.m_V = 1;
	pop		ebp
	ret
	*/
}

void main()
{
	/*
	push	ebp
	mov		ebp, esp
	*/

	CArg a;
	a.m_V = 0;
	/*
	sub		esp, 8							; a 공간 확보
	mov		dword ptr [ebp-4], 0			; ebp-4 위치의 0 대입
	*/

	Func(a);
	/*
	sub     esp,8							; 스택 확보
	mov     ecx,esp							
	lea     eax,[a]							; eax에 a의 유효 주소 값 가져옴
	push	eax								; 명시적 복사 생성자에 객체의 주소 값 전달
	call    CArg::CArg (0821451h)			; 복사 생성자 호출
	call    Func (0821325h)					; 함수 호출
	add     esp,8
	mov		esp, ebp
	pop		ebp
	ret
	*/
}
~~~
* 명시적 복사 생성자가 존재하면 컴파일러는 기본적인 멤버 객체의 메모리 복사조차 수행하지 않는다.
* 명시적 복사 생성자에게 전적으로 맡겨버린다.

### 7.4.3 참조에 의한 호출
값에 의한 호출을 정리하면 배열을 제외하고 기본 타입이나 클래스의 경우 전달되는 인자가 복사되기 된다.
* 오버헤드가 발생하며, 함수 호출 전후로 값이 바뀌지 않는다.
* 인자 자체를 복사

함수 호출 전후로 인자의 값이 변경되지 않아야 할 수도 있고 함수 호출 후에 반드시 인자의 값이 유지되어야 하는 경우도 있다.
* 이런 경우를 위해 참조에 의한 호출이 생겨났다.

참조에 의한 호출 기본 타입
~~~C++
void Func(int &arg)
{
	arg = 1;
	/*
	mov         eax,dword ptr [arg]			; eax = &a
	mov         dword ptr [eax],1			; a = 1
	*/
}

void main()
{
	int a = 0;
	/*
	mov         dword ptr [a],0
	*/
	Func(a);
	/*
	lea         eax,[a]						; eax = &a
	push        eax							; a의 주소 전달
	call        Func (0C1087h)				; 함수 Call
	add         esp,4						; 스택 인자 정리
	*/
}
~~~
* 단지 a의 주소만을 stack에 push
* 객체 자체가 복사되어서 전달되는 것이 아니라 객체의 주소가 전달됨
* 클래스 타입처럼 넘겨야 할 객체의 크기가 큰 경우에는 효율성이 극대화 된다.

배열의 경우에는 참조에 의한 호출 방식이나 값에 의한 호출이 똑같이 일치한다.
* 배열의 참조 타입 인자를 만드는 것은 int (&arg)[1]


배열의 값, 참조 전달의 차이
~~~C++
#include <iostream>

using namespace std;

typedef int TARR[3];

void FuncV(TARR arg)
{
	cout << "V - arr address : " << arg << endl;
	cout << "V - &arr address : " << &arg << endl;
	cout << "V - sizeof(arr) : " << sizeof(arg) << endl;
}

void FuncR(TARR &arg)
{
	cout << "R - arr address : " << arg << endl;
	cout << "R - &arr address : " << &arg << endl;
	cout << "R - sizeof(arr) : " << sizeof(arg) << endl;
}

void main()
{
	int arr[3] = { 0 };
	cout << "M - arr address : " << arr << endl;
	cout << "M - &arr address : " << &arr << endl;
	cout << "M - sizeof(arr) : " << sizeof(arr) << endl;

	FuncV(arr);
	/*
	lea         eax,[arr]
	push        eax
	call        FuncV (0C71104h)
	add         esp,4
	*/
	FuncR(arr);
	/*
	lea         eax,[arr]
	push        eax
	call        FuncR (0C712D5h)
	add         esp,4
	*/

	/*
	// 출력 결과
	M - arr address : 010FFE28
	M - &arr address : 010FFE28
	M - sizeof(arr) : 12
	V - arr address : 010FFE28
	V - &arr address : 010FFD54
	V - sizeof(arr) : 4
	R - arr address : 010FFE28
	R - &arr address : 010FFE28
	R - sizeof(arr) : 12
	*/
}
~~~
* 배열의 참조 전달의 경우 : & 참조 연산을 해도 주소와 값이 일치하게 나온다.
  * 배열의 이름이 곧 주소이기 때문
* 값 전달의 경우 : 배열의 메모리 주소와 다른 값을 보인다.
  * arg는 메모리 영역을 나타내고 그 영역 안의 값이 바로 arr의 주소이다.
  * TARR arg는 일종의 포인터로 취급된다는 것
  * &arg는 arg가 차지하는 메모리 영역의 주소를 나타내게 되므로 실제 배열의 주소와는 다르게 나온다.

참조에 의한 호출 클래스
~~~c++
class CArg
{
public:
	int m_E;
	int m_V;
};

void Func(CArg &arg)
{
	arg.m_V = 1;
	/*
	mov         eax,dword ptr [arg]			; eax = &a
	mov         dword ptr [eax+4],1			; a.m_V = 1;
	*/
}

void main()
{
	CArg a;
	a.m_V = 0;
	/*
	mov         dword ptr [ebp-0Ch],0
	*/
	Func(a);
	/*
	lea         eax,[a]				; eax = &a
	push        eax					; 인자 전달
	call        Func (0D111BDh)		; call
	add         esp,4				; 스택 정리
	*/
}
~~~
* 객체의 주소를 넘기는 것이다.
* 복사 생성자가 호출되지 않는다.
* 생성자 오버헤드가 사라지고 복사 손실 또한 사라진다.


복사 손실
* 가상 함수 테이블은 복사될 수 없다.
* CChild 자식 객체를 생성하고 CParent 부모 객체의 값 인자를 받는 함수에 전달할 경우
* vfptr은 복사가 불가능하고 CChild의 멤버는 복사할 곳이 없으므로 손실된다.
* 가상 함수 테이블이 복사되지 않으므로 CParent의 멤버 함수가 호출된다.
* 복사 손실을 피하기 위해서는 반드시 참조에 의한 호출 방식을 사용해야 한다.


### 7.4.4 참조 타입 const TYPE &
기본 타입의 경우에도 참조에 의한 호출을 반드시 사용해야만 하는 경우도 있다.
* 함수 호출로 인하여 인자 값이 변경되어도 변경된 값이 유지되어야만 하는 경우
* 다중 반환을 필요로 할 때 사용된다.

함수 안에서 인자가 변경되지 않음에도 참조에 의한 호출을 사용하는 경우
* int &arg를 인자로 받는 함수에 0이라는 상수를 전달하면 컴파일 에러가 발생한다.
* 참조 타입 인자는 객체의 주소를 넘기는 것이기 때문 - 메모리를 차지하지 않는 상수는 넘길 수 없다.
* const int &arg로 변경하면 상수도 인자로 넘길 수 있다.

const int &arg 인자
~~~c++
int Increase(const int &arg)
{
    return arg + 1;
}

void main()
{
    Increase(0);
    /*
    push    ecx                     ; 스택에 상수를 위한 영역을 마련
    mov     dword ptr [ebp-4], 0    ; 0을 대입
    lea     eax, [ebp-4]            ; ebp-4의 유효 주소를 얻어옴
    push    eax                     ; 인자를 전달
    call    Increase
    */
}
~~~
* 참조 타입에 const가 붙음으로 컴파일러는 상수를 위한 메모리 영역을 만들게 된다.
* 쓰기 금지를 지정하여 절대로 값이 바뀔 수 없게 하는 것

const TYPE & 인자
~~~c++
class CTest
{
public:
    CTest(int arg) { }
};

void Func(const CTest &arg) { }

void main()
{
    Func(0);
}
~~~
* 인자에 const가 없다면 컴파일 자체가 불가능하다.
* const를 붙여줌으로 상수에 의한 암시적 타입 변환을 허용한다.

결론은 클래스 객체를 인자로 넘길 경우, 함수 안에서 객체의 값이 변하지 않는다면 상수 참조 타입으로 넘겨야 한다.

## 7.5 반환 타입 (Return Type)

### 7.5.1 값에 의한 반환

int 반환 함수
~~~C++
int Func()
{
    /*
    push    ebp
    mov     ebp, esp
    */

    return 1;
    /*
    mov     eax, 1  ;  eax = 1
    pop     ebp
    ret
    */
}

void main()
{
    /*
    push    ebp
    mov     ebp, esp
    */

    int r = Func();
    /*
    push    ecx                         ; r 영역 확보
    call    Func                        ; 함수 호출
    mov     dword ptr [ebp-4], eax      ; r = 1
    mov     esp, ebp
    pop     ebp
    ret
    */
}
~~~
* eax에 반환 값인 1을 대입하고 있다.
* 함수의 반환값은 보통 eax 레지스터에 복사된 후에 함수가 반환된다.
* 반환 값을 받는 방법은 스택에 할당된 r 영역에 eax를 복사한다.

x86 시스템에서는 반환 값이 저장되는 용도로 eax 레지스터를 사용한다.
* x64 시스템에서는 rax를 사용한다.
* 물론 x64 시스템에서도 반환값이 4바이트라면 eax에 저장하는데 이는 rax의 하위 32비트를 의미한다.
* 즉, rax를 사용하는 것

__int64(long long)을 반환하는 경우
~~~c++
__int64 Func()
{
    /*
    push    ebp
    mov     ebp, esp
    */

    return 1;
    /*
    mov     eax, 1      ; eax = 1
    xor     edx, edx    ; edx = 0
    pop     ebp
    ret
    */
}

void main()
{
    /*
    push    ebp
    mov     ebp, esp
    */

    __int64 r = Func();
    /*
    sub     esp, 8                      ; 8바이트 영역 확보
    call    Func                        ; 함수 호출
    mov     dword ptr [ebp-8], eax      ; r 하위 32비트 = 1
    mov     dword ptr [ebp-4], edx      ; r 상위 32비트 = 0
    mov     esp, ebp
    pop     ebp
    ret
    */
}
~~~
* 반환 타입을 __int64로 바꾸면 어셈블리는 대폭 변화한다.
* edx 또한 반환 값으로 사용하고 있다.
* xor을 사용하면 0으로 만들 때 CPU 명령코드를 줄여서 효율을 높일 수 있다.
* 즉, eax와 edx를 사용하여 64비트 반환을 처리하고 있다.

반환 타입이 double일 때도 eax와 edx를 사용할까?
* 이 경우에는 꽤 복잡해진다.
* x64의 경우 xmn0 레지스터를 반환 값으로 사용한다.
* x86의 경우 특수한 어셈블리 명령을 사용한다.
* double의 경우에는 하위 32비트와 상위 32비트가 구조적으로 분리되기 어려운 면이 있기 때문이다.

배열 반환 함수
~~~c++
typedef int TARR[1];

TARR Func()
{
    int arg[1] = { 0 };
    return arg;
}
~~~
* 위 코드는 컴파일되지 않는다. - 함수는 배열을 반환할 수 없다.
* 대신 배열에 대한 포인터를 반환해야 한다고 컴파일러는 알려준다.
* 인자로 넘길 때도 배열 객체의 주소를 전달하였는데
* 실제로 배열을 반환할 수 있다고 하여도 반환되는 것은 배열 객체의 주소일 것이다.

배열 반환 함수
~~~c++
typedef int TARR[1];
TARR *Func()
{
    int arg[1] = { 0 };
    return (TARR*)arg;
    /*
    push    ebp
    mov     ebp, esp
    push    ecx
    mov     dword ptr [ebp-4], 0
    lea     eax, [ebp-4]            ; eax 레지스터를 통해 배열 객체의 주소를 반환한다.
    */
}
~~~
* 배열의 경우에도 eax 레지스터를 통해 반환한다.

반환 타입이 클래스 타입일 경우 전혀 다른 동작 방식이 필요해진다.

클래스 반환 함수 1
~~~C++
class CTest
{
public:
	int m_E;
	int m_V;
};

CTest Func()
{
	/*
	push	ebp
	mov		ebp, esp
	*/
	CTest t;
	t.m_V = 1;
	/*
	sub		esp, 8					; 8바이트 영역 확보
	mov		dword ptr [ebp-4], 1	; t.m_V = 1
	*/

	return t;
	/*
	mov		eax, dword ptr [ebp-8]	; eax = t.m_E
	mov		edx, dword ptr [ebp-4]	; edx = t.m_V
	mov		esp, ebp
	pop		ebp
	ret
	*/
}

void main()
{
	/*
	push	ebp
	mov		ebp, esp
	*/
	Func();
	/*
	sub		esp, 8					; 반환 임시 영역 8바이트 확보
	call	Func					; 함수 호출
	mov		dword ptr [ebp-8], eax	; ebp-8에 t.m_E 값 복사
	mov		dword ptr [ebp-4], edx	; ebp-4에 t.m_V 값 복사
	mov		esp, ebp
	pop		ebp
	ret
	*/
}
~~~
* 반환 타입이 클래스인 경우 컴파일러는 반환된 값을 보존하기 위해 스택에 임시로 클래스 크기의 영역을 확보한다.
* 함수가 반환한 후에 임시 영역에 반환된 값을 담아서 반환 값을 사용해야 할 때 접근하게 된다.
* 결국 8바이트 크기의 클래스는 eax, edx 2개의 레지스터 만으로도 반환될 수 있는 것이다.


그럼 8바이트보다 큰 경우에는?
* 함수가 반환을 한다는 것은 결국 callee가 자신을 호출한 caller에게 반환 값을 전달한다는 의미
* 값을 전달할 때처럼 callee가 caller에게 스택을 사용하여 반환하면 될 것이다.

그런데 caller가 반환 값의 크기를 어떻게 알고 정리할까?
* callee가 스택을 얼마나 사용하는지 컴파일 타임에는 알 수 없기 때문
* 바로 caller가 반환 타입의 크기만큼 미리 스택을 확보한 후에 callee를 호출하는 것이다.
* 즉, 미리 반환 값을 담을 공간을 확보하고 인자를 넘기는 것

클래스 반환 함수 2
~~~C++
__declspec(align(1)) class CTest
{
public:
    BYTE m_E[8];
    int m_V;
};

CTest Func()
{
    /*
    push    ebp
    mov     ebp, esp
    */

    CTest t;
    t.m_V = 1;
    /*
    sub     esp, 0Ch                ; t 영역 12바이트 확보
    mov     dword ptr [ebp-4], 1    ; t.m_V = 1
    */

    return t;
    /*
    mov     eax, dword ptr [ebp+8]      ; eax = 시작 주소
    mov     ecx, dword ptr [ebp-0Ch]    ; t의 첫째 4바이트 구해서
    mov     dword ptr [eax], ecx        ; eax 첫째 4바이트에 복사
    mov     edx, dword ptr [ebp-8]      ; t의 둘째 4바이트 구해서
    mov     dword ptr [eax+4], edx      ; eax 둘째 4바이트에 복사
    mov     ecx, dword ptr [ebp-4]      ; t.m_V 구해서
    mov     dword ptr [eax+8], ecx      ; eax 셋째 4바이트에 복사
    mov     eax, dword ptr [ebp+8]
    mov     esp, ebp
    ret
    */
}

void main()
{
    /*
    push    ebp
    mov     ebp, esp
    */

    Func();
    /*
    sub     esp, 18h                    ; 임시 영역 + 인자 영역 24바이트
    lea     eax, [ebp-18h]              ; eax = 임시 영역 시작 주소
    push    eax                         ; 인자 전달
    call    Func                        ; 함수 호출
    add     esp, 4                      ; 스택 정리
    mov     ecx, dword ptr [eax]        ; 인자 영역 첫째 4바이트 구해서
    mov     dword ptr [ebp-0Ch], ecx    ; 임시 영역 첫째 4바이트에 복사
    mov     edx, dword ptr [eax+4]      ; .. 반복
    mov     dword ptr [ebp-8], edx
    mov     eax, dword ptr [eax+8]
    mov     dword ptr [ebp-4], eax
    mov     esp, ebp
    ret
    */
}
~~~
* 클래스를 반환하는 함수를 호출하는 caller는 callee가 반환 값을 설정할 수 있는 반환 인자 영역과 함께 caller가 사용하기 위해 반환 결과를 저장하는 반환 임시영역을 스택에 마련한다.
* 즉, CTest가 12바이트라면 두 배 크기인 24바이트를 스택에 마련해놓은 것이다.
* 처음 12바이트는 callee가 반환 값을 저장하는 영역
* 다음 12바이트 영역은 caller가 반환 값을 임시로 저장하기 위해 사용하는 영역
* 호출자는 반환 영역을 callee에게 알려주기 위해 반환 인자 영역의 주소를 함수의 인자처럼 넘긴다.

반환 결과를 저장하기 위하여 반환 임시 영역이 필요한 것은 컴파일러의 원칙이다.
* VC++ 혹은 GCC의 최적화 컴파일을 진행하면, 반환 인자 영역을 반환 임시 영역으로 쓸 수도 있다.

### 7.5.2 참조에 의한 반환(Return by Reference)

참조에 의한 반환 - int&
~~~C++
int &Func()
{
    /*
    push    ebp
    mov     ebp, esp
    */

    int ret = 1;
    return ret;
    /*
    push    ecx                        ; ret 스택 영역 확보
    mov     dword ptr [ebp-4], 1       ; ret = 1
    lea     eax, [ebp-4]               ; eax = &ret
    mov     esp, ebp
    pop     ebp
    ret
    */
}

void main()
{
    /*
    push    ebp
    mov     ebp, esp
    */
    int r = Func();
    /*
    push    ecx                         ; r 영역 스택 확보
    call    Func                        ; 함수 호출
    mov     eax, dword ptr [eax]        ; eax = *(&ret)
    mov     dword ptr [ebp-4], eax      ; r = eax = ret
    mov     esp, ebp
    pop     ebp
    ret
    */
}
~~~
* 결국 eax를 통해서 반환되는 것은 실제 반환 결과가 저장되는 영역의 주소이고
* eax를 통해서 해당 반환 결과 영역에 접근할 수 있는 것이다.

반환 타입이 int&이라고 해서 int&로 받으면 절대 안된다.
* int &r은 int&이 가리키는 영역을 가리키게 된다. 
* 그런데 반환 결과 영역은 임시적이라서 해당 영역이 손상될 수 있다.

const int & 상수 반환의 경우 변화가 전혀 없다.


참조에 의한 반환 - 클래스
~~~C++
class CTest
{
public:
    BYTE m_E[8];
    int m_V;
}

CTest &Func()
{
    /*
    push    ebp
    mov     ebp, esp
    */

    CTest t;
    t.m_V = 1;
    /*
    sub     esp, 0Ch                ; t 영역 12 바이트 스택 확보
    mov     dword ptr [ebp-4], 1    ; t.m_V = 1
    */

    return t;
    /*
    lea     eax, [ebp-0Ch]          ; eax = &t
    mov     esp, ebp
    pop     ebp
    ret
    */
}

void main()
{
    /*
    push    ebp
    mov     ebp, esp;
    */

    Func();
    /*
    call    Func
    pop     ebp
    ret
    */
}
~~~

* 크기가 8바이트 이하거나 단순한 구조체의 경우를 제외하면 클래스는 참조 타입으로 반환해야한다.
* 위에서 본 결과 CTest t는 스택에 생성되어 있다.
* 따라서 반환 결과를 받은 후에 즉시 사용하거나, 다른 CTest 객체로 복사해두어야 한다.
* 실제로 스택에 생성된 객체를 참조 타입으로 반환하는 경우는 매우 드문일이다.

## 7.6 가변 인자 함수
가변 인자 함수에서 알아볼 것은 C++에서 직접 스택을 다루는 부분, 함수 사용 시 주의할 점

### 7.6.1 sprintf
대표적인 가변 인자 함수는 포맷 관련 함수
* ex printf, sprintf

~~~C++
void main()
{
    char buf[128];
    sprintf(buf, "%d %.2f %s", 1, 2.0, "Three");

    cout << buf << endl;
}
~~~

* 두 번째 인자가 바로 format, 형식을 지정하는 역할
* 가변 인자 함수에서 볼 때는 기준 인자가 된다.
* 기준 인자 : 가변 인자의 바로 이전 인자를 말한다.

기준 인자를 스택에서 찾고, 스택을 순차적으로 검색하면서, 가변 인자들을 각각 얻을 수 있다.

가변 인자란 : 인자 수가 정해지지 않은 것
* 최소한 함수 본체에서는 몇 개의 가변 인자를 처리할 것인지 정해져야 한다.

sprintf의 경우 format에서 찾을 수 있다.
* 꼭 sprintf 처럼 전달할 필요는 없다.
* 인자 수를 직접 인자로 넘기거나
* 함수 본체에서 무한 반복으로 처리하다가 특정 조건에서 중단하거나
* 결국 가변 인자 함수 본체를 어떻게 구현하느냐에 따라서 달라질 수 있다.

### 7.6.2 구현
가변 인자 함수의 형식
~~~C++
RETURN_TYPE FUNC_NAME(T1 arg1, T2 arg2, ---, TYPE vas, ...)
~~~
* 가변 인자 함수에서 가장 중요한 것은 vas와 ...이다.
* 즉, 가변 인자가 시작되기 바로 전 기준 인자
* vas 이후의 ... 형식이 가변 인자 함수라는 것을 지시하는 역할
* ... 지시가 있을 경우 컴파일러는 해당 함수가 가변 인자 함수인 것을 인지하고 에러나 경고를 발생시키지 않는다.

~~~C++
#include <iostream>

using namespace std;

void Func(int vas, ...)
{
	char *arg_ptr;
	arg_ptr = (char *)&vas; // 기준 인자인 ARG의 주소
	arg_ptr += sizeof(void *); // 포인터의 주소만큼 이동


	char a1 = *(char *)arg_ptr; // arg1 받아오기
	arg_ptr += sizeof(void *);  // 포인터 만큼 이동

	int a2 = *(int *)arg_ptr;   // arg2 받아오기
	arg_ptr += sizeof(void *);  // 이동

	double a3 = *(double *)arg_ptr; // 반복
	arg_ptr += sizeof(double);

	char *a4 = *(char **)arg_ptr;
	arg_ptr += sizeof(char *);

	arg_ptr = NULL;

	cout << a1 << a2 << a3 << a4 << endl;
}

int main()
{
	char a1 = '1';
	int a2 = 2;
	double a3 = 3.0;
	const char *a4 = "four";

	Func(0, a1, a2, a3, a4);

	return 0;
}
~~~
* char a1이 1바이트지만 스택에서는 4바이트를 차지한다.
* push, pop 기본 단위가 32비트 혹은 64비트를 사용하기 때문
* 인자들이 순서대로 있지 않다. - 반드시 선언 순서대로 할당할 필요는 없다.
* 컴파일러의 상황에 따라 달라진다.

함수 호출 규약은 오른쪽에서부터 왼쪽으로 순서대로 스택에 추가한다.
* 예제에서는 a4, a3, a2, a1, 0 순서대로 스택을 키워며 입력

vas 인자를 기준으로 인자의 크기만큼 메모리를 옮기면 가변 인자 모두를 접근할 수 있다.

arg_ptr은 가변 인자들을 가리키기 위한 포인터
* arg_ptr을 조작하면서 가변인자에 접근

함수 호출 규약에 의해서 차례대로 스택에 정렬되어 전달한다.
* 첫 번째 인자의 주소를 구하면 순차적으로 각각의 인자를 구할 수 있다.
* 이것으로 끝일까? - 그렇지 않다.
* C++에서는 좀 더 쉽게 가변 인자 함수를 작성하는 매크로를 정의해두었다.

매크로 활용
~~~C++
#include <iostream>
#include <stdarg.h>

using namespace std;

void Func(int vas, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, vas);
	char a1 = va_arg(arg_ptr, char);
	int a2 = va_arg(arg_ptr, int);
	double a3 = va_arg(arg_ptr, double);
	char* a4 = va_arg(arg_ptr, char *);
	va_end(arg_ptr);

	cout << a1 << a2 << a3 << a4 << endl;
}

int main()
{
	char a1 = '1';
	int a2 = 2;
	double a3 = 3.0;
	const char *a4 = "four";
	Func(0, a1, a2, a3, a4);

	return 0;
}
~~~
* 핵심 키워드 : va_list, va_start, va_arg, va_end
* 사실 코드를 따라가보면 typedef나 define 뿐
* 이 키워드를 사용하려면 \<stdarg.h>를 포함해야 한다.

va_list
* char*의 재정의일 뿐이다.
* 1바이트 단위로 메모리 주소를 가감할 수 있기 때문

va_start
* arg_ptr을 첫 번째 가변 인자의 주소로 설정, 두 번째 인자로 반드시 기준인자를 넣어야 한다.

va_arg
* 두 번째 인자로 타입 자체를 넣는다.
* 함수가 아니라 전처리 매크로이기 때문에 가능하다.
* arg_ptr이 가리키는 스택 주소를 입력된 타입으로 변환하여 값을 얻고
* 동시에 arg_ptr을 다음 가변 인자를 가리키도록 변경한다.
* 타입의 크기에 따라 적절히 스택 기본 단위로 맞추는 역할
* char, short - 4, 이상 크기인 경우 8을 더해준다는 의미
* 즉, 스택 기본 단위의 배수가 되도록 더한다는 것

va_arg가 사용하는 매크로
~~~C++
#define _INTSIZEOF(n)  ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))
~~~
* 이 매크로를 사용할 경우 n 에 4바이트 이하인 타입을 넣으면 4가 나오고
* 이상의 타입(클래스)를 넣을 경우 8이 나온다.


va_end
* 단순히 arg_ptr에 NULL(0)을 대입한다.


### 7.6.3 문자열 클래스
가변 인자 함수는 대부분 포맷 문자열 관련 함수이다.
* 문자열 클래스와 밀접한 관계가 생겨날 수 밖에 없다.
* 포맷 함수가 문자열 클래스 구조와 설계에 영향을 끼치기도 하였다.

C++에서 대표적으로 사용되는 문자열 클래스라면 C++라이브러리에서 제공되는 string이 있다.
* STL의 컨테이너처럼 취급되므로 STL string이라고도 한다.

std::string을 printf와 같은 가변 인자 함수에 인자로 넘기면 런타임 에러가 발생한다.
* 메모리 위치가 다르기 때문
* 시작주소로 부터 4바이트가 떨어진 위치부터 실제 문자열 데이터가 담긴다.

메모리 복사로 객체를 복사할 수 없는 타입일 경우 가변 인자로 넘기지 않겠다는 것

### 7.6.4 클래스 타입
char, int, double과 같은 기본 타입을 넘겨보았다.

문자열 클래스도 넘겨보았으나 컴파일러에 의존성이 있음을 알 수 있었다.

클래스 타입은 그럼 가변 인자로 온전히 넘길 수 있는가?

~~~C++
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

/*
// 출력 결과
CFunc : 2
VAFunc : 1
*/
~~~
정리하면 다음과 같다.
* 가변 인자는 값에 의한 호출 방식으로 전달되는데
* 복사 생성자가 호출되지는 않으며, 오직 메모리 복사만 일어난다는 것이다.
* 따라서 클래스를 가변 인자로 전달할 경우 의도한 대로 객체를 전달하지 못할 수도 있다.

### 7.6.5 스택 정리
함수 호출 규약에서 cdecl과 stdcall의 가장 큰 차이점
* cdecl : caller가 스택 정리, 가변 인자 함수를 만들 수 있다.
* stdcall : callee가 스택 정리

x64 Calling Convention처럼 caller가 스택을 정리하는 함수 호출 규약에서는 가변 인자 함수가 가능하다.


~~~C++
void main()
{
    printf("%d", 1);
    printf("%d", 1, 2);         // 2
    printf("%d", 1, 2, 3);      // 3
}
~~~

* 2, 3이 잘못된 코드 같지만 컴파일 에러는 발생하지 않는다.
* printf가 format 만을 판단해서 스택을 정리한다면 2,3의 경우 시스템 자체가 멈출 것이다.
* 그러나 caller인 main 함수는 인자를 몇 개 넣었는지 알고 있기 때문에 적절히 스택을 정리할 수 있다.
* 즉, 가변 인자 함수의 스택 정리는 오직 caller만이 할 수 있다.

## 7.7 클래스 멤버 함수
C++ 클래스의 멤버 함수는 말 그대로 클래스의 멤버이자 함수이다.
* 즉, 클래스 멤버로서의 속성과 일반 함수의 성질도 그대로 가지고 있는 것

### 7.7.1 멤버 함수 위치
멤버 함수는 클래스 멤버 객체의 메모리 영역에 포함되는 것이 아니다.
* 다른 함수와 마찬가지로 함수 코드 영역에 있을 뿐
* 클래스 멤버 함수이기 때문에 지정된 범위 안에서 호출될 수 있다는 차이가 있다.

### 7.7.2 thiscall
32비트 x86 호출 규약 중 멤버 함수를 위한 호출 규약이 따로 있다.
* thiscall : 이름에서 보이듯 멤버 함수의 필수 인자인 this를 넘기는 규칙 포함
* x64의 통합 함수 호출 규약에는 thiscall의 내용이 포함되어 있다.

비정적 멤버 함수에 대해서는 기본적으로 thiscall이 지정된다.
* 물론 다른 함수 호출 규약 또한 지정할 수 있다.

thiscall
~~~C++
class CTest
{
public:
	void Func_thiscall() {}
	void __cdecl Func_cdecl() {}
	void __stdcall Func_stdcall() {}
};

int main()
{
	CTest t;

	t.Func_thiscall();
	/*
	lea		ecx, [t]				; ecx = &t
	call	CTest::Func_thiscall
	*/

	t.Func_cdecl();
	/*
	lea		eax, [t]
	push	eax						; push &t
	call	CTest::Func_cdecl
	add		esp, 4
	*/

	t.Func_stdcall();
	/*
	lea		eax, [t]
	push	eax						; push &t
	call	CTest::Func_stdcall
	*/

	return 0;
}
~~~
* 비정적 멤버 함수에 대해서 각각의 함수 호출 규약을 강제로 지정한 것이다.
* x86에서만 의미가 있으며, x64에서는 무시된다.

특별한 지정이 없는 경우 : thiscall
* thiscall 또한 stdcall과 마찬가지로 callee가 스택을 정리할 책임을 가진다.
* thiscall은 ecx혹은 rcx 레지스터를 이용하여 this를 넘기는 것이 일반적

그에 반해 cdecl과 stdcall이 지정될 수 있다.
* cdecl에서는 레지스터가 아닌 스택을 이용하여 this를 전달한다.

### 7.7.3 this
this는 비정적 멤버 함수 자신이 어떤 객체로부터 호출되었는지를 알려주는 지시자 역할을 한다.
* this는 해당 객체의 주소를 나타내는 일종의 포인터

this 키워드가 보이지 않는다고 해서 컴파일러가 ecx 레지스터를 통해 객체의 주소를 전달하지 않아도 되는 것은 아니다.
* 컴파일러가 전달한 ecx 레지스터를 통해서 멤버 함수에서 클래스의 다른 멤버에 접근할 수 있기 때문

만일 비정적 멤버 함수에서 클래스의 다른 멤버에 접근하지 않는다면 객체의 주소 자체가 불필요하다는 것
* 즉, 객체의 주소가 잘못되어도 아무 문제가 없다는 것

~~~C++
#include <iostream>

using namespace std;

class CTest
{
public:
	void Func() {}
	void Func1() 
	{
		Func();
		cout << this << endl;
	}

	void Func2()
	{
		Func();
		cout << this << m_Value << endl; // runtime error
	}

	int m_Value;
};


int main()
{
	CTest *pT = NULL;

	pT->Func1();
	pT->Func2();

	return 0;
}
~~~
* 많은 개발자들이 잘못된 객체에 대해서 멤버 함수를 호출할 경우 그 즉시 런타임 에러가 발생한다고 생각
* 정확히 런타임 에러는 오직 잘못된 멤버 객체에 접근할 때 발생하는 것이다.

Func2() 에서 NULL 포인터의 m_Value에 접근할 때 해당 영역이 보호 영역이기 때문에 접근 자체로만으로 예외가 발생하는 것

운이 좋다면 this가 잘못된 주소라도 m_Value의 오프셋 위치가 접근 가능한 영역이라면 예외가 발생하지 않고 넘어갈 수도 있다.
* 그로 인해 버그를 찾기 정말 어려워진다.

잘못된 this와 가상 함수
~~~C++
class CTest
{
public:
    virtual void Func() {}
};

void main()
{
    CTest *pT = NULL;
    pT->Func();     // Runtime Error
}
~~~
* 존재하지도 않는 vfptr를 참조하여 런타임 에러

정적 멤버 함수와 this
~~~C++
class CTest
{
public:
    static void Func()
    {
        cout << this << endl; // Compile Error
    }
};
~~~
* 애초에 컴파일 자체가 되지 않는다.
* this를 사용할 수 없기 때문에
* staic과 virtual 키워드는 절대로 양립할 수 없다.


### 7.7.4 이름 탐색 규칙
C++에서 제일 중요한 특징은 바로 중복 정의와 재정의
* 컴파일러는 어떤 기준에 의해 함수를 탐색할까?

유효 범위를 기준으로 탐색
* 전역 함수의 유효 범위 : 전체
* 멤버 함수의 경우 : 클래스 - 각각의 클래스는 그 자체가 유효 범위
* 부모 클래스와 자식 클래스가 있는 경우 : 부모 클래스의 유효 범위는 자식 클래스를 포함한다.

### 7.7.5 const 멤버 함수
const가 지정된 객체(변수)는 변경될 수 없다. 컴파일러는 const 객체에 대해서 상태를 변경시키는 코드에 대해서 컴파일을 거부한다.


~~~C++
class CTest
{
public:
    CTest()
    {
        m_Val = 0;
    }

    void Set(int arg)
    {
        m_Val = arg;
    }

    void Func() { }

    int m_Val;
};

void main()
{
    const CTest t;
    t.Set();        // Error
    t.Func();       // Error
}
~~~
* const 객체는 일반 멤버 함수를 호출할 수 없다.
* const 객체가 호출할 수 있는 멤버 함수를 제공하는데 그것이 바로 const 멤버 함수

const 멤버 함수를 만드는 방법
* 멤버 함수를 선언 및 정의할 경우 함수 인자 정의가 끝나는 곳에 const를 붙인다.

~~~C++
class CTest
{
public:
    CTest()
    {
        m_Val = 0;
    }

    void Set(int arg) const
    {
        m_Val = arg;       // Error
    }

    void Func() const { }

    int m_Val;
};

void main()
{
    const CTest ct;
    ct.Func();

    CTest t;
    t.Func();
}
~~~
* const 객체가 아닌 경우에도 const 멤버 함수를 호출할 수 있다.
* const 멤버 함수 내에서 멤버 변수를 변경하면 에러가 발생한다.


const 멤버 함수 - 허용되지 않는 구문
~~~C++
class CTest
{
public:
    CTest()
    {
        m_Val = 0;
    }

    void Func() {}

    void Func1() const
    {
        Func();         // Error
    }

    CTest &Func2() const
    {
        return *this;   // Error
    }

    CTest *Func3() const
    {
        return this;    // Error
    }

    const CTest &Func4() const
    {
        return *this;   // OK
    }

    const CTest *Func5() const
    {
        return this;    // OK
    }

    int m_Val;
};
~~~
* const 멤버 함수는 객체를 변경시키는 일체의 코드도 허용하지 않는다.
* 조금이라도 낌새가 보이면 컴파일 에러

안되는 경우
1. const 멤버 함수 내부에서 비 const 멤버 함수를 호출할 수 없다.
2. 객체 자신 혹은 포인터를 반환 받을 수 없다. - 받은 측에서 변경할 수 있기 때문에
3. 따라서 const 객체 혹은 포인터를 반환해야 한다.


const 멤버 함수 - const 필요 이유
~~~C++
class CParent
{
public:
	CParent()
	{
		m_Val = 0;
	}

	virtual void VFunc() // A
	{
		m_Val = 1;
	}

	int m_Val;
};

class CChild : public CParent
{
	virtual void VFunc() // B
	{

	}
}

void main()
{
	const CChild c;
	const CParent *pP = &c;
	pP->VFunc();
}
~~~
* 위 코드는 실제로는 에러가 발생하지만 컴파일 가능하다고 가정
* virtual 함수의 경우 컴파일러는 컴파일 시점에 어떤 함수가 실행될지 알 수 없다.
* const 지정이 없을 경우 컴파일러가 함수를 분석하는 것만으로는 한계가 있으므로, 어쩔 수 없이 const 지정자를 쓸 수밖에 없다.

참고로, const 멤버 함수는 비 const 멤버 함수와 완전히 다른 함수로 취급된다.
* 인자 타입, 반환 타입이 모두 같아도 const의 유무로 서로 다른 함수로 구분
* 결국 const가 함수의 시그니처에 포함

const 멤버 함수 - 우선 순위
~~~C++
class CTest
{
public:
	void Func()
	{
		cout << "Non Const Function" << endl;
	}

	void Func() const
	{
		cout << "Const Function" << endl;
	}
};

void main()
{
	CTest t;
	t.Func();

	const CTest ct;
	ct.Func();
}
~~~
* 같은 이름의 Func가 비 const와 const로 함께 존재
* 즉, const의 여부로 중복 정의가 가능함
* 비 const 객체의 경우 비 const 함수를 우선 선택
* const 객체의 경우 const 함수를 선택


const 멤버 함수는 STL에서 많이 사용된다.

STL map의 경우
~~~C++
class CTest
{
public:
	BOOL operator < (const CTest &rhs) const
	{
		return m_Val < rhs.m_Val;
	}

	int m_Val;
};

void main()
{
	std::map<CTest, CTest*> test_map;

	CTest t;
	test_map[t] = &t;	// Error
}
~~~
* 위 코드는 에러가 발생한다.
* 템플릿 인수를 const CTest에서 추론할 수 없습니다.
* 간단히 STL map은 트리 구조를 사용한다.
* 트리가 구성될 때는 키의 대소 비교가 필요하다.
* 즉, 키 객체에 대해서 연산자 < 가 정의되어야만 한다.
* operator에서 const가 생략되면 컴파일 에러가 발생한다.

왜 const가 필요할까?
* STL map에서 const 객체에 operator < 를 호출하기 때문
* STL 컨테이너는 대부분 내부에서 const 객체를 기준으로 함수를 호출한다.
* 따라서 STL에 호환될 수 있는 클래스 작성시에는 const 멤버 함수가 필수이다.

const 멤버 함수 정리
* const 클래스 객체는 절대 멤버가 변경되면 안된다.
* 따라서 const 멤버 함수만을 호출 가능하며
* const 멤버 함수 내에서 멤버가 변경되는 코드 작성 시 컴파일 에러
* const 키워드는 가상 함수로 인해 반드시 필요
* STL 호환 클래스 작성시에는 const 멤버 함수를 필수로 구현해야 하는 경우있음


## 7.8 함수 객체(Functor)
함수는 아니지만 함수처럼 사용할 수 있는 클래스
* 함수 객체 혹은 functor

핵심은 opertor()를 재정의하는데 있다.

### 7.8.1 구현
~~~C++
#include <iostream>

using namespace std;

class CFunctor
{
public:
	CFunctor()
	{
		m_Sum = 0;
	}

	int operator() (int arg)
	{
		m_Sum += arg;
		return m_Sum;
	}

	int m_Sum;
};

void main()
{
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	CFunctor f;
	for (int i = 0; i < 10; i++)
	{
		f(array[i]);
	}

	cout << f.m_Sum << endl;
}
~~~
* 함수 객체는 클래스이기 때문에 자기 자신의 정보를 보관할 수 있다.
* 물론 함수 내에 정적 지역 변수를 사용할 순 있다.
* 그러나 1~10, 11~20 까지의 합을 각각 구하려면 어떻게 할까?
* 함수 객체는 단순히 객체를 2개 만들면 된다.


### 7.8.2 for_each
for_each는 STL에 도입된 반복문이다.
* 템플릿 기반으로 내부에서는 for문을 사용하고 있다.
* 물론 for_each 구현은 컴파일러 제작사마다 다를 수 있다.

함수 객체는 for_each와 STL에 잘 어울린다.


for_each 구현
~~~C++
template<typename Iterator, typename Functor>
inline Functor for_each(Iterator first, Iterator last, Functor func)
{
	for (; first != last; ++first)
	{
		func(*first);
	}

	return (func);
}
~~~
* for_each 문은 내부적으로 for 구문을 사용한다.
* 그리고 for문 안에서 func를 호출하도록 되어있는데
* Functor는 실제로 함수 객체 뿐만 아니라 함수 포인터도 될 수 있다.
* for_each는 반복문이라 하지만 실제로는 반복을 수행하는 함수이다.
* 반환 값은 실제로 for문에서 사용된 함수 객체 혹은 함수 포인터인 func이다.

~~~C++
#include <iostream>

using namespace std;

class CFunctor
{
public:
	CFunctor()
	{
		m_Sum = 0;
	}

	int operator() (int arg)
	{
		m_Sum += arg;
		return m_Sum;
	}

	int m_Sum;
};

void main()
{
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; 

	CFunctor f;
	cout << for_each(&array[0], &array[10], f).m_Sum << endl;
}
~~~

* for_each의 반환 값이 함수 객체이므로 m_Sum에 바로 접근 가능하다.

## 7.9 람다(Lambda)
람다를 간단히 말하자면 '이름 없는 함수'라고 할 수 있다.

람다의 구조와 원리, std::function의 구현 원리도 살펴볼 것이다.

### 7.9.1 람다 기본
~~~C++
void main()
{
	int x = 1;

	cout << [x](int arg)->int{ return x + arg; } (10) << endl;
}
~~~
* 람다는 대괄호 []로 시작된다. [x]처럼 main의 지역변수 x가 쓰여있는데.
* 변수를 캡쳐한다. 라고 말한다. - 즉, 외부 변수를 캡쳐하는 기능 수행
* 괄호()는 일반 함수처럼 (parameter)를 정의한다.
* 화살표 -> 는 반환 타입을 나타낸다.
* 블록 {}은 함수 본체를 정의하는 부분이다.
* 블록 끝에 (10)을 붙인 것은 arg에 10을 인자로 넘기면서 람다를 호출한다는 것이다.

기존 함수와의 가장 큰 차이점은 이름이 없다는 것
* 일회적인 성격이 강하기 때문

람다는 보통의 함수가 아니기 때문에 함수처럼 정의할 수 없다.
* 전역적으로 람다를 정의하면 컴파일 에러
* 람다는 함수 안에서만 정의될 수 있다.
* 람다 정의는 하나의 식이거나 식의 일부로 간주되기 때문에 식이 끝나는 곳에 ;를 붙여야 한다.

### 7.9.2 람다 문법
~~~C++
[Capture_Variables] (Parameters)->Return_Type { Body };
~~~
* 위의 식에서 가장 특이한 부분은 바로 Capture_Variables이다.
* 일반적으로 함수의 본체에서 전역 변수와 지역 변수를 사용할 수 있다.
* 람다에서는 추가적으로 외부 변수를 사용할 수 있다.
* 외부 변수 : 람다가 정의된 함수의 지역변수
* 캡쳐를 통해서 외부 변수의 속성을 지정할 수 있다. - 값 변수, 참조 변수
* Capture_Variables는 외부 변수의 값, 참조 여부를 결정한다.
* Capture_Variables에 의해 지정된 외부 변수는 람다 본체에 인자처럼 전달되어 지역 변수로 사용된다.

Capture_Variables
~~~C++
void main()
{
	int x1 = 100;
	int x2 = 10;
	int x3 = 1;

	// 모두 값 변수로 지정
	int R1 = [=]()->int{ return x1 + x2 + x3; }();

	// 모두 참조 변수로 지정
	int R2 = [&]()->int{ return x1 + x2 + x3; }();

	// x1만 참조 나머지 모두 값 변수로 지정
	int R3 = [=, &x1]()->int{ return x1 + x2 + x3; }();

	// x1만 값 나머지 모두 참조 변수로 지정
	int R4 = [&, x1]()->int{ return x1 + x2 + x3; }();
}
~~~


### 7.9.3 람다 중복
람다 본체에서 또 다른 람다를 정의할 수 있다.
~~~C++
void main()
{
	int x = 100;

	return [x] (int arg1) -> int
			{
				return [x, arg1] (int arg2) -> int
					{
						return x + arg1 + arg2;
					} (1);
			} (10);
}
~~~

### 7.9.4 멤버 함수와 람다
클래스의 멤버 함수에서도 람다를 정의하고 사용할 수 있다.
~~~C++
class CTest
{
public:
	int m_Value;
	int Func()
	{
		return [=](int arg) -> int
				{
					return m_Value + arg;
				} (1);
	}
}

void main()
{
	CTest t;
	t.m_Value = 10;
	cout << t.Func() << endl;
}
~~~
* 람다 본체에서 사용할 수 있는 변수는 전역, 지역, 외부 변수 뿐이다.
* m_Value는 무엇일까?
* 정답은 바로 this이다. - 지역 변수

Capture_Variables [=]
* 이것을 풀어쓰면 [this]가 된다.
* this가 멤버 함수 Func의 지역변수이기 때문에 람다 입장에서는 외부 변수가 되는 것이다.
* this는 상수 포인터 변수이기 때문에 값 변수로만 지정될 수 있다.

멤버 함수에서도 람다를 중복해서 사용할 수 있다.


### 7.9.5 람다 구조
람다는 컴파일러에 의해 처리되는 새로운 문법이지만 어셈블리를 살펴보면 함수 객체(Functor)와 비슷한 면을 찾을 수 있다.

~~~C++
#include <iostream>

using namespace std;

class CLambda
{
public:
	CLambda(int &vx, int &rx) : _vx(vx), _rx(rx) {}

	int operator()(int arg)
	{
		_rx = 10;
		return _vx + _rx + arg;
	}

	const int _vx;
	int &_rx;
};

void main()
{
	int vx = 100;
	int rx = 0;

	/*
	 push        1
	 lea         eax,[rx]
	 push        eax
	 lea         ecx,[vx]
	 push        ecx
	 lea         ecx,[ebp-110h]
	 call        `main'::`2'::<lambda_1>::<lambda_1> (0F91870h)		; 클래스 생성자랑 비슷한 느낌
	 mov         ecx,eax
	 call        `main'::`2'::<lambda_1>::operator() (0F91950h)		; operator() 호출
	 mov         dword ptr [R1],eax
	*/
	int R1 = [vx, &rx](int arg) -> int // 람다 캡처 부분 - 클래스 생성자의 초기화 리스트와 똑같이 동작
		{	// operator() 재정의
			rx = 10;
			return vx + rx + arg;
		} (1);

	/*
	 lea         eax,[rx]
	 push        eax
	 lea         ecx,[vx]
	 push        ecx
	 lea         ecx,[lambda]
	 call        CLambda::CLambda (0FB13BBh)
	*/
	CLambda lambda(vx, rx);
	/*
	 push        1
	 lea         ecx,[lambda]
	 call        CLambda::operator() (0FB10FFh)
	 mov         dword ptr [R2],eax
	*/
	int R2 = lambda(1);

	cout << R1 << endl;
	cout << R2 << endl;
}
~~~
* 클래스 함수 객체와 람다는 동일하게 동작한다.
* 람다 캡처 부분에서 생성자의 초기화 리스트 처럼 동작하고
* 함수의 본체 부분에서 operator()를 오버로딩 하는 것
* 실제로 람다는 하나의 함수 객체처럼 취급되기 때문에 저장할 수 있고
* 인자처럼 전송할 수 있다.

### 7.9.6 람다 저장
람다는 하나의 객체이다.
* operator()가 단 하나만 재정의된 이름 없는 함수 객체
* 따라서 변수에 저장도 할 수 있지만 복제도 가능하다는 것을 의미한다.
* (함수는 함수 포인터에 저장할 순 있지만 복제는 어렵다.)

함수의 저장
~~~C++
int Func(int arg)
{
	return arg;
}

void main()
{
	int (*pFunc1)(int); // 1
	pFunc1 = &Func;
	int R1 = pFunc1(1);

	typedef int (*PFUNC)(int); // 2
	PFUNC pFunc2 = &Func;
	int R2 = pFunc2(1);

	auto pFunc3 = &Func; // 3
	int R3 = pFunc3(1);
}
~~~
Func를 저장하기 위한 변수를 만드는 방법 2가지
* 1번 처럼 함수 포인터 타입 변수 만들기
* 2번 처럼 typedef를 이용하여 함수 포인터 타입 정의
* 두 방법의 공통점은 바로 이름이 필요하다는 것
* 그런데 람다는 이름이 없으므로 위 2가지 방법이 불가능하다.

C++11에 도입된 auto 키워드
* auto는 알아서 대입될 객체의 타입으로 변신
* 따라서 함수를 저장하는 것도 간단하다.


auto로 람다 저장하기
~~~C++
auto lambda = [] (char *str) { cout << str << endl; };

void main()
{
	lambda("Hello World!");
}
~~~

람다를 전역 변수 lambda에 저장하는 예제
* 왜 전역 스코프에서 정의가 될까?
* 사실 람다의 저장은 프로세스 시작 시 호출되는 CRT Startup 함수에서 이뤄진다.
* 반환 타입이 void일 경우 ->void를 생략 가능하다.

람다 저장 2
~~~C++
void main()
{
	int x = 10;
	int y = 1;

	auto lambda = [x, &y] () -> int
			{
				return x + y;
			};
	
	int R1 = lambda();

	x = 20;	// 적용 안됨
	y = 2;	// 적용됨

	int R2 = lambda();

	cout << R1 << endl;
	cout << R2 << endl;
}
~~~
* 지역 변수를 변경하면 적용이 안되는 이유
* 값 변수는 람다의 초기화에서 이뤄진다.
* 참조 변수는 변경이 가능하다.

람다를 저장할 수는 있게 되었지만, 아직 미흡하다.
* 외부 변수를 캡쳐하는 람다의 경우 전역 변수나 멤버 변수에 저장할 수 없기 때문

전역 변수 람다 저장 안되는 예제
~~~C++
auto g_Lambda; // Complie Error

void Func()
{
	int x = 10;
	g_Lambda = [x] () -> int { return x; };
}

void main()
{
	Func();
	cout << g_Lambda() << endl;
}
~~~
* auto 키워드는 오직 초기화될 때 대입되는 객체의 타입으로 변경되기 때문에 컴파일 에러
* 따라서 초기화 없이는 auto 변수를 사용할 수 없다.

결국 함수 안에서 정의된 람다를 저장할 방법은 오직 해당 함수에서 선언된 auto 변수를 사용하는 것뿐

람다를 전역 변수에 영구적으로 저장하여 어떤 함수에서도 사용할 수 있는 방법
* STL의 std::function

std::function 람다 저장
~~~C++
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
~~~
* STL의 std::function을 사용하려면 \<functional> 헤더를 포함해야 한다.
* std::function 객체를 생성할 때는 템플릿 인자로 람다 함수의 시그니처를 입력 int 타입 인자를 하나 받아서 int 타입을 반환하므로 int(int)

### 7.9.7 람다 저장 클래스
람다 저장 클래스를 만들기 전 알아야 할 것
* 템플릿 사용 방법
* 템플릿 가변 인자 (옛날에는 0개, 1개, 2개 각각 전부 구현했다.)


람다를 저장하기 위해서는 람다의 타입을 반드시 구해야 한다. - 템플릿

~~~C++
template<typename LAMBDA>
void Func(LAMBDA arg)
{
	LAMBDA lambda = arg;
	lambda(1);
}

void main()
{
	Func([] (int arg) { cout << arg << endl; });
}
~~~
* auto 처럼 LAMBDA 타입은 실제 대입된 람다의 타입이 된다.
* 또한 람다는 결국 함수와 같으므로, 즉 인자와 반환 타입이 있다.
* 시그니처 또한 타입으로 받아들여 처리해야 한다.

RETURN_TYPE(ARG_TYPE1, ARG_TYPE2, ... );
* 예를 들어 double 타입 인자 둘을 받아 int를 반환하는 함수 시그니처
* int(double, double)

템플릿 가변 인자를 사용하는 방법
~~~C++
int Func(double a, double b)
{
	return (int) (a + b);
}

template<typename RT, typename ...ATs>
RT TFunc(ATs... args)
{
	return Func(arg...);
}

void main()
{
	int R = TFunc<int, double, double>(3.2, 3.8);
}
~~~
* ...ATs : typename이 가변 개수만큼 있다는 것

람다 저장 클래스
~~~C++
// 람다 인터페이스
template<typename RT, typename... ATs>
class CLambdaInterface
{
public:
	RT Call(ATs... args)
	{
		return _Call(args...);
	}

	virtual RT _Call(ATs... args) = 0; // 내부 가상 함수
};


// 람다를 실제로 저장하는 클래스이기 때문에 LAMBDA 타입이 반드시 필요하다.
template<typename LAMBDA, typename RT, typename... ATs>
class CLambda : public CLambdaInterface<RT, ATs...>
{
public:
	CLambda(const LAMBDA &lambda)
	{
		m_pLambda = new LAMBDA(lambda);
	}

	~CLambda()
	{
		if (m_pLambda)
		{
			delete m_pLambda;
		}
	}

	virtual RT _Call(ATs... args)
	{
		return (*m_pLambda)(args...);
	}
	
	LAMBDA *m_pLambda;
};


template<typename T>
class CFunction; // CFunction<T> 전방 선언

// CFunction을 정의하는 시점에 전달할 수 있는 템플릿 인자는 오직 함수의 시그니처 뿐
template<typename RT, typename... ATs>
class CFunction<RT(ATs...)>
{
public:
	CFunction()
	{
		m_pLambdaInterface = NULL;
	}

	template<typename LAMBDA>
	CFunction(const LAMBDA &lambda) // 람다의 타입이 알려지는 순간
	{
		m_pLambdaInterface = new CLambda<LAMBDA, RT, ATs...>(lambda);
	}

	template<typename LAMBDA>
	CFunction<RT(ATs...)> &operator=(const LAMBDA &lambda) // 람다의 타입이 알려지는 순간
	{
		if (m_pLambdaInterface)
		{
			delete m_pLambdaInterface;
		}

		m_pLambdaInterface = new CLambda<LAMBDA, RT, ATs...>(lambda);
		return *this;
	}

	RT operator() (ATs... args) // 결국 CFunction 객체는 Functor가 된다.
	{
		return m_pLambdaInterface->Call(args...);
	}

	// CLambda의 부모 클래스이므로 자식 객체의 포인터를 대신할 수 있기 때문
	CLambdaInterface<RT, ATs...> *m_pLambdaInterface;
};
~~~

사용 코드
~~~C++
#include <iostream>
#include "CFunction.h"

using namespace std;

CFunction<double(int, int)> lambda;		// Lambda Object
CFunction<double(int, int)> func;		// Function Object

double Divide(int a, int b)
{
	if (b != 0)
	{
		return (double)a / b;
	}

	return 0;
}

int main()
{
	double vx = 0.3;
	double rx = 0;

	lambda = [vx, &rx](int a, int b) -> double
		{
			rx = 0.4;
			return vx + rx + a + b;
		};

	func = &Divide;
	cout << lambda(1, 2) << endl;
	cout << func(1, 2) << endl;

	return 0;
}
~~~