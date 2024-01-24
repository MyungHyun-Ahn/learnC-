# Chapter 06 클래스
## 6.1 구조체와 클래스의 차이
접근 지정자에서 차이가 난다.
* struct : public
* class : private

struct가 public인 이유는 C언어와 하위 호환성을 위함

class는 C++에서 캡슐화와 정보 은닉의 개념을 구현하기 위함

class는 구조체를 포함하는 개념


## 6.2 클래스의 메모리 구조
### 6.2.1 메모리 배치 규칙
* 변수의 메모리 위치는 선언 순서와 일치한다.
* 구조체 패딩, 구조체 멤버 맞춤

### 6.2.2 멤버의 접근
멤버 접근 어셈블리
~~~c++
CTest t;

t.m_Char = 'A';
mov     byte ptr [ebp-18h], 41h ; 0

t.m_Int = 1;
mov     byte ptr [ebp-14h], 1   ; 4

t.m_Double = 3.14;
fld     qword ptr [_real ...]   ; 8
fstp    qword ptr [ebp-10h]
~~~


### 6.2.3 클래스 크기
클래스의 크기는 반드시 0보다 커야한다.
* 멤버가 없는 경우 : 1
* 가상 함수가 있는 경우 : 4 or 8

가상 함수가 있는 경우 가상 함수 테이블을 가리키는 포인터를 멤버로 가지게 된다.
* vfptr

## 6.3 생성자와 소멸자
### 6.3.1 암시적 생성자와 소멸자
생성자와 소멸자가 명시적으로 정의되어 있지 않을 때, 특별히 필요하지 않다면 컴파일러는 굳이 암시적으로 정의하지 않는다.

생성자의 경우
~~~C++
// 생성자 자체가 불필요하므로 암시적 생성자는 없다.
class CTest1
{
public:
    BYTE m_Data;
};

// 이미 생성자가 명시적으로 정의되어 있다.
class CTest2
{
public:
    CTest2() {}
    BYTE m_Data;
};

class CTestP3
{
public:
    BYTE m_Data;
}

// 생성자 자체가 불필요하므로 암시적 생성자는 없다.
class CTest3 : public CTestP3
{
public:
    BYTE m_Data;
}

class CTestP4
{
public:
    BYTE m_Data;
}

// 이미 생성자가 명시적으로 정의되어 있다.
class CTest4 : public CTestP4
{
public:
    CTest4() {}
    BYTE m_Data;
}

class CTestP5
{
public:
    CTest5() {}
    BYTE m_Data;
}

// CTestP5의 생성자가 정의되어 있다.
// CTest5의 생성자에서 호출해주어야 한다.
// 따라서 반드시 CTest5는 생성자가 필요하다.
// 컴파일러가 암시적으로 생성자를 생성한다.
class CTest5 : public CTestP5
{
public:
    BYTE m_Data;
}

class CTestP6
{
public:
    CTest6() {}
    BYTE m_Data;
}

// 이미 명시적으로 정의되어 있다.
class CTest6 : public CTestP6
{
public:
    CTest6() {}
    BYTE m_Data;
}
~~~

소멸자의 경우
~~~C++
// 소멸자 자체가 불필요하므로 암시적 소멸자는 없다.
class CTest1
{
public:
    BYTE m_Data;
};

// 이미 소멸자가 명시적으로 정의되어 있다.
class CTest2
{
public:
    ~CTest2() {}
    BYTE m_Data;
};

class CTestP3
{
public:
    BYTE m_Data;
}

// 소멸자 자체가 불필요하므로 암시적 생성자는 없다.
class CTest3 : public CTestP3
{
public:
    BYTE m_Data;
}

class CTestP4
{
public:
    BYTE m_Data;
}

// 이미 소멸자가 명시적으로 정의되어 있다.
class CTest4 : public CTestP4
{
public:
    ~CTest4() {}
    BYTE m_Data;
}

class CTestP5
{
public:
    ~CTest5() {}
    BYTE m_Data;
}

// CTestP5의 소멸자가 정의되어 있다.
// CTest5의 소멸자에서 호출해주어야 한다.
// 따라서 반드시 CTest5는 소멸자가 필요하다.
// 컴파일러가 암시적으로 소멸자를 생성한다.
class CTest5 : public CTestP5
{
public:
    BYTE m_Data;
}

class CTestP6
{
public:
    ~CTest6() {}
    BYTE m_Data;
}

// 이미 명시적으로 정의되어 있다.
class CTest6 : public CTestP6
{
public:
    ~CTest6() {}
    BYTE m_Data;
}
~~~

* 컴파일러 입장에서 new / delete의 구현이 달라질 수 있기 때문에 중요하다.

### 6.3.2 생성자와 소멸자의 호출 순서

생성자와 소멸자
~~~C++
class CParent
{
public:
    CParent()
    {
        cout <<
    }

    ~CParent()
    {
        cout <<
    }
}

class CChild : public CParent
{
public:
    CChild()
    [
        선처리 영역 시작
        부모 클래스 생성자 호출
        멤버가 클래스 타입일 경우 생성자 호출
        .. 기타 선처리 ..
        선처리 영역 끝
    ]
    {
        cout <<
    }

    ~CChild()
    {
        cout <<
    }
    [
        후처리 영역 시작
        멤버가 클래스 타입일 경우 소멸자 호출
        부모 클래스 소멸자 호출
        .. 기타 후처리 ..
        후처리 영역 끝
    ]
}
~~~

출력 결과
1. CParent 생성자
2. CChild 생성자
3. CChild 소멸자
4. CParent 소멸자

생성자 블록은 부모 -> 자식 순서

소멸자의 경우 자식 -> 부모 순서


### 6.3.3 virtual 소멸자
왜 소멸자는 virtual로 지정해야 하는가?

생성자와 소멸자
~~~c++
class CParent
{
public:
    CParent() {}
    virtual ~CParent() {}
};

class CChild : public CParent
{
public:
    CChild() {}
    virtual ~CChild() {}
}

int main()
{
    CParent *pParent = new CChild; // delete를 수행하면 CChild의 소멸자가 호출, 이어서 부모인 CParent의 소멸자도 호출
    delete pParent;
}
~~~

소멸자가 virtual로 지정되지 않았다면 어떤일이 발생할까?
* CParent만 호출되고 CChild의 소멸자는 호출되지 않을 것이다.
* CChild는 virtual을 지정하지 않아도 virtual이 된다.
* 확실하게 가상 함수임을 알려주기 위해 써주는 것이 좋다.

가상 함수가 한개라도 있는 클래스는 메모리 오프셋 0지점에 vfptr이라는 가상함수포인터가 생성된다.
* C++에 추가로 도입된 RTTI 정보를 이용하기 위해서는 반드시 필요하다.
* RTTI는 실행 시간에 객체의 타입 정보를 이용하는 것을 의미

어떤 클래스가 절대로 부모 클래스로 사용되지 않을 것이라면
* vfptr을 가질 필요가 없다.
* 괜히 구조체 크기만 증가한다.


## 6.4 복사 생성자와 복사 대입 연산자
메모리 복사 방식
~~~c++
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
~~~
* 객체의 생성과 메모리 복사 방싱 4가지
* 모두 동일한 어셈블리 코드를 생성한다.
  

클래스의 경우에도 큰 변화는 없다.
* 숨겨진 코드가 생성된다는 차이가 있다.
* 컴파일러가 작성하고 보이지 않게 수행하기 때문에 전혀 의도치 않은 동작을 수행할 수도 있다.

### 6.4.1 복사 생성자
~~~c++
class CTest
{
public:
	CTest()
	{
		m_Value = 1;
	}

	CTest(const CTest &Obj)
	{
		// 여기서 아무 일도 하지 않기 때문에 쓰레기 값
	}

	void ShowValue()
	{
		cout << m_Value << endl;
	}

	int m_Value;
};

int main()
{
	CTest t0;
	t0.m_Value = 3;
	/*
	 lea         ecx,[t0]
	 call        CTest::CTest (0A13C5h) ; 기본 생성자
	 mov         dword ptr [t0],3
	*/

	CTest t1(t0); // 1 - 복사 생성자 호출
	t1.ShowValue(); // 쓰레기 값
	/*
	 lea         eax,[t0]
	 push        eax
	 lea         ecx,[t1]
	 call        CTest::CTest (0A115Eh) ; 복사 생성자
	*/

	CTest t2 = t0; // 2 - 복사 생성자 호출
	t1.ShowValue(); // 쓰레기 값
	/*
	 lea         eax,[t0]
	 push        eax
	 lea         ecx,[t2]
	 call        CTest::CTest (0A115Eh) ; 복사 생성자
	*/

	CTest t3; 
	/*
	 lea         ecx,[t3]
	 call        CTest::CTest (0A13C5h) ; 기본 생성자
	*/
	t3 = t0; // 3 - 실제로 객체를 먼저 생성하고 대입 연산자 호출
	/*
	 mov         eax,dword ptr [t0]
	 mov         dword ptr [t3],eax ; 대입 연산
	*/
	t3.ShowValue();

	return 0;
}
~~~

복사 생성자란 자신의 (const) 참조 타입을 인자로 받는 생성자
* ClassName(const ClassName& obj)
* const가 없다면 const 형 객체를 넣을 때 컴파일 에러가 발생한다.
* 가능하면 const 지정자를 넣는 것이 안전하다.

복사 생성자의 선처리 영역
* 부모 클래스의 복사 생성자가 호출될 것 같지만.
* 기본 생성자를 호출한다.

명시적 복사 생성자 동작
* 명시적으로 정의된 복사 생성자에서 초기화 리스트를 통해서 다른 생성자를 호출하지 않는 한 선처리 영역에서는 부모 클래스와 멤버 클래스의 기본 생성자가 호출된다.

암시적 복사 생성자
~~~C++
class CTest
{
public:
	CTest()
	{
		m_Value = 1;
	}

	void ShowValue()
	{
		cout << m_Value << endl;
	}

	int m_Value;
};

int main()
{
	CTest t0;
	t0.m_Value = 3;

	CTest t1(t0);
	/*
	 mov         eax,dword ptr [t0]
	 mov         dword ptr [t1],eax
	*/
	t1.ShowValue(); // 3 출력

	CTest t2 = t0;
	/*
	 mov         eax,dword ptr [t0]
	 mov         dword ptr [t2],eax
	*/
	t1.ShowValue(); // 3 출력

	CTest t3;
	/*
	 lea         ecx,[t3]
	 call        CTest::CTest (0A313C0h)
	*/
	t3 = t0;
	/*
	 mov         eax,dword ptr [t0]
	 mov         dword ptr [t3],eax
	*/

	t3.ShowValue(); // 3 출력

	return 0;
}
~~~
* 명시적인 복사 생성자가 존재하지 않을 때 컴파일러는 코드상으로는 보이지 않는 복사 생성자를 자동으로 추가하는데 이것을 암시적 복사 생성자라고 한다.
* 즉, 어떤 클래스던 복사 생성자는 반드시 존재해야한다.

암시적 복사 연산자의 선처리
~~~c++
CTest(const CTest& Obj)
[ // 선처리 영역 시작
  1. 부모 클래스의 복사 생성자 호출
  2. 멤버가 클래스 타입일 경우 복사 생성자 호출
  3. 멤버가 기본 타입일 경우 메모리 복사
  4. 멤버가 배열일 경우 원소의 타입에 따라 2, 3 수행
  5. 멤버가 참조 타입일 경우 대상 복사
  ... 기타 선처리
] // 선처리 영역 끝
{
    // 생성자 블록
}
~~~
* 즉, 부모 클래스와 멤버 클래스에 대해 복사 생성자가 호출된다.
* 기본 타입일 경우 메모리 복사 또한 이루어진다.

왜 명시적 복사 생성자와 암시적 복사 생성자가 다르게 동작할까?
* 객체를 복사 : 두 객체의 메모리 영역만 다른 뿐 내부의 값은 일치시키는 것
* 얕은 복사 : 굉장히 많은 문제를 일으킴

얕은 복사
* 두 객체의 멤버 포인터가 같은 객체를 가리키고 있을 수 있다.
* 한쪽이 객체를 소멸시키면 다른 쪽은 소멸된 객체를 가리킬 수 있다.
* 이런 문제가 발생할 여지가 있는 경우 명시적으로 복사 생성자를 다시 정의하라는 것

정리하면
* 명시적 복사 생성자 : 부모 멤버 기본 생성자 호출 - 깊은 복사하도록 작성해야 함
* 암시적 복사 생성자 : 부모 멤버 복사 생성자 호출 - 얕은 복사가 수행됨

### 6.4.2 복사 대입 연산자
명시적 복사 대입 연산자
~~~c++
class CTest
{
public:
	CTest &operator = (const CTest &obj)
	{
		m_Value = 3;
		return *this;
	}

	void ShowValue()
	{
		cout << m_Value << endl;
	}

	int m_Value;
};

int main()
{
	CTest t0;
	t0.m_Value = 5;

	CTest t1(t0); // 복사 생성자
	t1.ShowValue();

	CTest t2 = t0; // 복사 생성자
	t2.ShowValue();

	CTest t3;
	t3 = t0; // 복사 대입 연산자
	/*
	 lea         eax,[t0]
	 push        eax
	 lea         ecx,[t3]
	 call        CTest::operator= (081106Eh)
	*/
	t3.ShowValue();
}
~~~

암시적 복사 대입 연산자
~~~c++
CTest& operator=(const CTest& obj)
{
    1. 부모 클래스에 대해서 복사 대입 연산자 호출
    2. 멤버가 클래스 타입일 경우 복사 대입 연산자 호출
    3. 멤버가 기본 타입일 경우 메모리 복사
    4. 멤버가 배열 타입일 경우 원소의 타입에 따라 2, 3 수행
    
    return *this; // 마지막에는 자기 자신을 반환한다.
}
~~~
* 복사 대입 연산자는 생성자와는 다르게 선처리 영역이나 후처리 영역이 없다.
* 그냥 함수이기 때문에

객체 간 대입 연산을 할 경우 주의할 사항
* 클래스의 멤버 중 참조 타입이나 const 지정자가 있는 상수 타입이 있는 경우 암시적 복사 대입 연산자로 인해 컴파일 에러가 발생한다.
* 멤버마다 대입 연산을 수행하는데 참조 타입이나 const 타입은 초기화할 때만 대입 연산을 수행할 수 있기 때문
* 이럴 때는 직접 명시적으로 복사 대입 연산자를 정의해야한다.

### 6.4.3 배열 타입의 복사
~~~c++
int A[3] = {1, 2, 3};
int B[3];
B = A; // 컴파일 에러 - 배열의 이름은 l-value가 될 수 없다.
~~~
* 배열의 경우 불가능하다..

클래스의 경우에는 가능하다.
~~~c++
class CTest
{
public:
    int m_Array[3];
}

int main()
{
    CTest A;
    A.m_Array[0] = 1;
    A.m_Array[1] = 2;
    A.m_Array[2] = 3;

    CTest B = A;
}
~~~

* 배열을 복사할 경우 반복문을 통하여 요소를 일일이 대입하거나 통으로 복사해야 한다.
* 하지만 클래스의 멤버 배열의 경우 컴파일러가 배열의 복사를 진행하는 코드를 넣어준다.
* 컴파일러는 각각 배열의 원소를 하나씩 대입해준다.
* 클래스 배열 때문에 일일이 대입한다. 복사 생성자를 호출해야 하기 때문에

### 6.4.4 실전 연습

### 6.4.5 복사 생성자와 복사 대입 연산자의 올바른 사용
암시적 복사 생성자나 암시적 복사 대입 연산자는 완벽한 복사를 제공할 수는 없다.
* 객체 간 복사의 경우 명시적 복사 생성자와 명시적 복사 대입 연산자를 손수 구현해야 한다.

### 6.4.6 객체의 값에 의한 호출 (Call by Value of Object)
객체의 값에 의한 호출을 하는 경우에도 복사 생성자가 호출된다.
* 함수가 끝나는 시점에서 소멸자도 호출된다.
* 즉, 값에 의한 호출은 비용이 너무 크다.

참조 타입의 객체를 전달
* 생성자와 소멸자가 전달되지 않는다.
* const 지정자를 붙이면 객체가 함수에서 절대 수정되지 않을 것을 의미한다.
* 만일 수정하려 하면 컴파일 에러

값에 의한 호출과 참조를 의한 호출의 같은 이름의 함수를 만들 수 없다.
* 오버로딩 불가
* T와 T&를 중복 정의하면 컴파일러는 어떤 타입의 함수를 호출해야 할지 결정할 수 없기 때문에 컴파일 에러가 발생한다.

### 6.4.7 복사 금지 클래스
복사를 금지하는 클래스를 만들 수 있다.
* 복사 연산자, 생성자를 선언만 하고 구현하지 않는다.
    * 복사를 시도하는 경우 링크 에러
* 복사 연산자, 생성자를 private 영역에 둔다.
* Boost 라이브러리의 noncopyable


### 6.4.8 RValue Reference의 이용
일반적으로 STL을 비롯하여 자료구조 클래스들은 깊은 복사를 수행한다.
* 안좋은 효율을 보인다.

따라서 임시 객체를 통하여 복사 생성을 할 때 우측값 참조를 이용하여 얕은 복사를 수행하도록 하면 된다.


### 6.4.9 등가 연산자
* 직접 오버로딩해서 만들어야 한다.

## 6.5 초기화 리스트
생성자 초기화
~~~C++
class CTest1
{
public:
	CTest1()
	{
		m_Value = 3;
	}
	/*
	 push        ebp
	 mov         ebp,esp
	 sub         esp,0CCh
	 push        ebx
	 push        esi
	 push        edi
	 push        ecx
	 lea         edi,[ebp-0Ch]
	 mov         ecx,3
	 mov         eax,0CCCCCCCCh
	 rep stos    dword ptr es:[edi]
	 pop         ecx
	 mov         dword ptr [this],ecx
	 mov         ecx,offset _5EA21858_il@cpp (091C000h)
	 call        @__CheckForDebuggerJustMyCode@4 (0911325h)
		{
			m_Value = 3;
	 mov         eax,dword ptr [this]
	 mov         dword ptr [eax],3
		}
	 mov         eax,dword ptr [this]
	 pop         edi
	 pop         esi
	 pop         ebx
	 add         esp,0CCh
	 cmp         ebp,esp
	 call        __RTC_CheckEsp (091123Fh)
	 mov         esp,ebp
	 pop         ebp
	 ret
	*/

	int m_Value;
};
~~~

초기화 리스트 초기화
~~~C++
class CTest2
{
public:
	CTest2() : m_Value(3)
	{
	}
	/*
	 push        ebp
	 mov         ebp,esp
	 sub         esp,0CCh
	 push        ebx
	 push        esi
	 push        edi
	 push        ecx
	 lea         edi,[ebp-0Ch]
	 mov         ecx,3 ; 값을 바로 대입
	 mov         eax,0CCCCCCCCh
	 rep stos    dword ptr es:[edi]
	 pop         ecx
	 mov         dword ptr [this],ecx
	 mov         ecx,offset _5EA21858_il@cpp (091C000h)
	 call        @__CheckForDebuggerJustMyCode@4 (0911325h)
	*/

	int m_Value;
};
~~~


### 6.5.1 초기화 리스트의 원리
생성자의 원형 코드에는 선처리 과정이 있다.
* 부모 멤버 클래스의 기본 생성자를 호출한다.

즉, 선처리 영역에는 이미 호출할 생성자가 정해져 있다.

초기화 리스트를 사용하면 이 선처리 과정을 제어할 수 있다.

~~~c++
CChild(int arg) : CParent(arg), M_Member(arg + 1), m_CValue(arg + 2)
~~~
* 원하는 생성자를 명시적으로 설정해서 호출할 수 있다.
* 여기에 적은대로 순서를 따라가지 않고, 오직 클래스의 정의를 따른다.

### 6.5.2 초기화 리스트 사용시 주의점
멤버라고 해서 모두 초기화 리스트에 넣을 수 있는 것은 아니다.
* 부모의 멤버 : 멤버라는 것은 자기 자신 클래스에서 선언된 것이다.
* 선처리 영역에서 처리되는 것이다. 부모 클래스의 생성자를 호출하자

### 6.5.3 그 외 초기화 리스트를 사용하는 경우
* 상수 타입과 참조 타입 멤버는 반드시 초기화 리스트를 사용해야만 한다.
* 절대 생성자 블록에서 초기화가 불가능하다.

## 6.6 타입 변환 연산자

~~~c++
operator TYPE()
{
    변환 코드
}
~~~
* TYPE에는 int, double 등 다양한 타입이 올 수 있다.
* 반환형이 없다. 이미 TYPE으로 정해져 있기 때문에


### 6.6.1 문자열 클래스의 타입 변환 연산자
~~~c++
int main()
{
    CString CStringObj = "CString";
    std::string stringObj = "string";
    const char *p1 = CStringObj;                // 1 OK
    const char *p2 = CStringObj.GetBuffer();    // 2 OK
    const char *p3 = stringObj;                 // 3 Error
    const char *p4 = stringObj.c_str();         // 4 OK
}
~~~

암시적 변환, 명시적 변환?
* const char *p3 = stringObj; // 암시적 변환
* const char *p3 = (const char\*)stringObj; // 명시적 변환

위의 1부분을 따라가면 타입 변환 연산자가 오버로딩된 것을 볼 수 있다.
~~~c++
operator PCXSTR() const throw()
{
    return (m_pszData);
}
~~~
* 즉, CString에는 const char*로 변환하는 연산자가 정의되어 있다.

STL의 string 클래스는 타입 변환 연산자가 정의되지 않았기 때문에 컴파일 에러가 발생한다.

sprintf(Buf, "%s", stringObj); // std::string 객체
* 위와 같이 사용하면 메모리 자체가 복사되어 들어가기 때문에
* Buf에 쓰레기 값이 들어가게된다.

CString은 완벽히 호환된다.
* 실제로 문자열 포인터를 가리키는 m_pszData가 들어있기 때문에


## 6.7 상속 (Inheritance)
### 6.7.1 멤버 접근 지정자
기본적으로 클래스의 모든 멤버는 자기 자신 외에는 비공개를 원칙으로 한다.
* 각각의 멤버에 접근 권한을 지정하기 위해 멤버 접근 지정자를 사용한다.

1. public : 모두에게 공개
2. private : 자기 자신 혹은 friend로 지정한 것에게
3. protect : 파생 클래스에서만 접근 가능

### 6.7.2 friend
함수 혹은 클래스 등을 지정하여 자신의 private 멤버에 접근할 수 있도록 함


### 6.7.3 상속 접근 지정자

class 자식클래스 : [접근지정자] 부모클래스1, [접근지정자] 부모클래스2, ...

상속 접근 지정자가 하는 일은 부모 클래스에 속한 멤버들이 자식 클래스로 상속될 때 접근 지정을 변경하는 역할을 한다.

변경되는 것 public : protected : private
* public 상속 : public : protected : 접근 불가
* protected 상속 : protected : protected : 접근 불가
* private 상속 : private : private : 접근 불가

### 6.7.4 상속 클래스의 메모리 구조
자식 클래스의 메모리 구조에는 부모 클래스의 메모리 구조가 온전히 포함된다.

메모리 구조
* CParent : m_PValue 4byte
* CChild : m_CValue 4byte

부모의 것이 먼저

같은 이름 멤버의 메모리 구조
* CParent : m_Value 4byte
* CChild : m_Value 4byte

C++은 코드에서 중복된 이름을 검색하는 경우 정해둔 규칙에 따라 정한다.
* 자식 클래스부터 탐색을 시작

CChild.m_Value -> CChild의 변수\
CChild.CParent::m_Value -> CParent의 변수


### 6.7.5 정적 멤버의 상속
클래스 내부에서 static 선언하는 것 : 정의는 없는것
* 외부에서 정의도 해준다.

~~~c++
class CTest
{
public:
    static int stInt;
}

int CTest::s_Value; // cpp 파일에서
~~~

정적 멤버 또한 상속이 가능하다.
* 당연히 정적 멤버는 하나이다.

CParent::s_Value = 1;\
CChild::s_Value = 2;
* 결국 최종 s_Value의 값은 부모 자식 모두 2

이름이 겹치는 경우
* CChild::CParent::s_Value = 3; // 이와 같이 CParent의 정적 변수를 찾는다.
* CChild::s_Value = 2; // CChild의 정적 변수

### 6.7.6 기본 클래스 함수의 상속
클래스에는 기본적으로 필요한 함수들이 있다.
* 생성자, 소멸자, 대입 연산자 등등 타입 변환 연산자
* 이런 기본 클래스 함수들은 상속이 되는 경우도 있고 아닌 경우도 있다.
* 상속이 된다는 의미 : 부모 클래스의 F라는 함수를 재정의 하지 않아도 자식이 사용할 수 있다는 것


기본 클래스 함수의 상속 여부

상속이 불가능한 것
1. 생성자는 상속이 되지 않는다. + 소멸자
   * 자식 클래스의 생성자가 부모 클래스의 생성자를 자동 호출하게 되어 있는 것
   * 절대 상속으로 인한 것은 아니다.
2. 대입 연산자도 상속이 되지 않는다.

상속이 가능한 것
1. 타입 변환 연산자는 상속이 된다.
2. 재정의된 일반 연산자도 상속된다.

## 6.8 다중 상속 (Multiple Inheritance)
### 6.8.1 다중 상속의 메모리 구조
~~~c++
class CParentA
{
public:
	CParentA()
	{
		m_AVal = 1;
		m_AVal2 = 1;
	}

	int GetAVal()
	{
		return m_AVal;
		/*
		 mov         eax,dword ptr [this]
		 mov         eax,dword ptr [eax]
		*/
	}

	int m_AVal;
	int m_AVal2;
};

class CParentB
{
public:
	CParentB()
	{
		m_BVal = 2;
	}

	int GetBVal()
	{
		return m_BVal;
		/*
		 mov         eax,dword ptr [this]
		 mov         eax,dword ptr [eax]
		*/
	}

	int m_BVal;
};

class CChild : public CParentA, public CParentB
{
public:
	CChild()
	{
		m_CVal = 3;
	}

	int GetCVal()
	{
		return m_CVal;
		/*
		 mov         eax,dword ptr [this]
		 mov         eax,dword ptr [eax+0Ch] ; 오프셋 계산이 들어감 this에서 + 0Ch 위치의 값을 가져옴
		*/
	}

	int m_CVal;
};

int main()
{
	CChild c;
	/*
	 lea         ecx,[c]
	 call        CChild::CChild (0C21384h)
	*/

	CParentA *pA = &c;
	/*
	 lea         eax,[c]
	 test        eax,eax
	 je          __$EncStackInitStart+46h (0C22B92h)
	 lea         ecx,[c]
	 add         ecx,8
	 mov         dword ptr [ebp-128h],ecx
	 jmp         __$EncStackInitStart+50h (0C22B9Ch)
	 mov         dword ptr [ebp-128h],0
	 mov         edx,dword ptr [ebp-128h]
	 mov         dword ptr [pB],edx
	*/

	CParentB *pB = &c;
	/*
	 lea         eax,[c]
	 test        eax,eax
	 je          __$EncStackInitStart+46h (0C22B92h)
	 lea         ecx,[c]
	 add         ecx,8 ; 오프셋을 컴파일러가 계산하여 바꿔줌
	 mov         dword ptr [ebp-128h],ecx
	 jmp         __$EncStackInitStart+50h (0C22B9Ch)
	 mov         dword ptr [ebp-128h],0
	 mov         edx,dword ptr [ebp-128h]
	 mov         dword ptr [pB],edx
	*/

	CChild *pC = &c;
	/*
	 lea         eax,[c]
	 mov         dword ptr [pC],eax
	*/

	int Ret1 = pA->GetAVal();
	/*
	 mov         ecx,dword ptr [pC]
	 add         ecx,8 ; 아예 호출전에 this 포인터 오프셋 계산을 해서 넘긴다.
	*/
	int Ret2 = pC->GetBVal();
	int Ret3 = pC->GetCVal();

	std::cout << "pA : " << pA << "\n\0";
	std::cout << "pB : " << pB << "\n\0";
	std::cout << "pC : " << pC << "\n\0";

	return 0;
}
~~~
* CParentA : m_AVal : 4 // Address of CParentA & CChild
* CParentB : m_BVal : 4 // Address of CParentB
* CChile : m_CVal : 4

pB의 주소 값만 다르다.
* 컴파일러가 적절히 대입해서 실제 부모 클래스의 메모리 시작 주소를 가리키도록 변경시킨다.
* 오프셋을 더함

왜 그렇게 하는가?
* 각 클래스가 각 클래스의 멤버 함수를 호출할 때 멤버 함수가 사용할 수 있는 실제 클래스의 시작 주소를 넘겨줘야 하기 때문에

주소가 바뀌는 포인터 변환 과정은 주로 다중 상속이 사용될 때 이루어진다.
* 다중 상속에서만 발생하는 일은 아니다.

### 6.8.2 다중 상속의 문제점(Diamond 구조)
~~~c++
class CTop
{
public:
	int m_Top;
};

class CMiddleA : public CTop
{
public:
	int m_MiddleA;
};

class CMiddleB : public CTop
{
public:
	int m_MiddleB;
};

class CBottom : public CMiddleA, public CMiddleB
{
public:
	CBottom()
	{
		// m_Top = 10; // 모호하다며 컴파일 에러
		CMiddleA::m_Top = 10;
		m_MiddleA = 21;
		m_MiddleB = 22;
		m_Bottom = 30;
	}

	int m_Bottom;
};

int main()
{
	CBottom c;
	/*
	// 메모리 구조
	0x0095FC48  cc cc cc cc  ????
	0x0095FC4C  0a 00 00 00  .... // m_Top
	0x0095FC50  15 00 00 00  .... // m_MiddleA
	0x0095FC54  0a 00 00 00  .... // m_Top
	0x0095FC58  16 00 00 00  .... // m_MiddleB
	0x0095FC5C  1e 00 00 00  .... // m_Bottom
	0x0095FC60  cc cc cc cc  ????
	*/
	/*
	// 어떤 멤버를 사용할지 지정해서 할당
	0x00FBF768  cc cc cc cc  ????
	0x00FBF76C  0a 00 00 00  .... // CMiddleA::m_Top
	0x00FBF770  15 00 00 00  ....
	0x00FBF774  cc cc cc cc  ????
	0x00FBF778  16 00 00 00  ....
	0x00FBF77C  1e 00 00 00  ....
	0x00FBF780  cc cc cc cc  ????
	*/

	return 0;
}
~~~

* 범위 연산을 지정해서 수행해야 한다.
* 두 번째 m_Top은 메모리를 낭비하는 구조가 된다.

## 6.9 가상 상속(Virtual Inheritance)
모호성 문제와 메모리 낭비 문제를 일거양득으로 해결할 수 있는 방법

### 6.9.1 가상 기저 클래스(Virtual Base Class)

가상 기저 클래스 예제
~~~c++
class CTop
{
public:
	CTop() {}

	int m_Top;
};

class CMiddleA : virtual public CTop
{
public:
	int m_MiddleA;
};

class CMiddleB : virtual public CTop
{
public:
	int m_MiddleB;
};

class CBottom : public CMiddleA, public CMiddleB
{
public:
	CBottom()
	{
		m_Top = 10;
		m_MiddleA = 21;
		m_MiddleB = 22;
		m_Bottom = 30;
	}

	int m_Bottom;
};

int main()
{
	CBottom c;
	/*
	메모리 구조
	CBottom
	CMiddleA	vbptr A
				m_MiddleA
	CMiddleB	vbptr B
				m_MiddleB
				m_Bottom
	CTop		m_Top
	*/

	/*
	// 메모리 구조
	0x004FFA04  cc cc cc cc  ????
	0x004FFA08  48 7b 1f 00  H{.. // vbptr A
	0x004FFA0C  15 00 00 00  .... // m_MiddleA
	0x004FFA10  54 7b 1f 00  T{.. // vbptr B
	0x004FFA14  16 00 00 00  .... // m_MiddleB
	0x004FFA18  1e 00 00 00  .... // m_Bottom
	0x004FFA1C  0a 00 00 00  .... // m_Top
	0x004FFA20  cc cc cc cc  ????
	*/

	return 0;
}
~~~
* 가상 기저 클래스는 여러번 상속 되더라도 메모리 상 1개만 존재

생성자 호출 순서
1. CBottom이 호출되며 -> CMiddleA, CMiddleB를 호출
2. 그럼 CTop의 생성자는 누가?
3. 가상 기저 클래스를 상속받는 최종 클래스인 CBottom에서 한번만 호출

메모리 구조
* 예제의 주석 참고
* 컴파일러마다 제각각 다르다. 주석은 VC++ 기준

vbptr이라는 포인터 메모리 영역
* Virtual Base Table : 그것을 가리키는 테이블

위 예제에서는 실제로 vbptr이 두번 추가되면서 클래스의 크기가 더 커졌다.
* 가상 기저 클래스로 만들만큼 크기가 큰 경우에 의미가 있다.

성능은 오히려 떨어진다.
* 가상 상속을 사용한 경우 vbptr을 한번 거쳐야만 하는데, 성능 저하를 가져온다.

애초에 다이아몬드 구조 자체를 사용하지 않도록 만드는 것이 효과적일 수 있다.

### 6.9.2 가상 상속의 구조
vbptr (virtual base table) : 특정 테이블을 가리키는 포인터
* 오프셋 정보만 포함하면 될 것 같은데? 왜 테이블
* 가상 기저 클래스가 1개만 있는 것은 아니기 때문에
* 추가로 vbptr의 맨 처음 항목은 자기 자신이 들어간다. + 최소한 두개

~~~C++
	/*
	메모리 구조
	CBottom
	CMiddleA	vbptr A    --->  0
				m_MiddleA        20 - CTop의 오프셋
	CMiddleB	vbptr B    --->  0
				m_MiddleB        12 - CTop의 오프셋
				m_Bottom
	CTop		m_Top
	*/
~~~

* CTop은 가상 기저 클래스가 되며 전체 클래스 구조에서 가장 밑부분에 위치하게 된다.
* virtual 키워드를 사용하여 상속받은 자식 클래스는 반드시 vbptr 메모리 영역이 생성되며 클래스 구조의 가능하면 위쪽에 위치하게 된다.
* 더 상위에 있을 수 있는 것이 있다는 것이다.
* vfptr(가상 함수 테이블)의 경우 vbptr보다 위쪽으로 간다.


첫번째 오프셋이 0인데 필요할까?
* vfptr이 있는 경우 음수가 될 수 있다.
* 즉, vbptr이 클래스 메모리 시작 위치가 아닌 경우

CMiddleA와 CMiddleB에 가상함수가 존재하는 경우
~~~C++
	/*
	메모리 구조
	CBottom
	CMiddleA	vfptr A
                vbptr A    --->  -4
				m_MiddleA        24 - CTop의 오프셋
	CMiddleB	vfptr B          
                vbptr B    --->  -4
				m_MiddleB        12 - CTop의 오프셋
				m_Bottom
	CTop		m_Top
	*/
~~~

vbptr이 메모리 시작주소에 위치하지 않는 경우2
~~~C++
class CD1A
{
public:
    int m_D1A;
};

class CD1B
{
public:
    int m_D1B;
};

class CD2 : public CD1A, virtual public CD1B
{
public:
    int m_D2;
};

/*
    메모리 구조
    CD2
    CD2' -  m_D1A  - CD1A
            vbptr ---> -4
            m_D2       8
    CD1B    m_D1B
*/
~~~

## 6.10 클래스 타입 변환
### 6.10.1 클래스 타입 변환 기초
~~~c++
int main()
{
    int i = 3;
    double d1 = i;              // OK
    double d2 = (double)i;      // OK
    double d3 = (double&)i;     // OK - 메모리 공간을 8바이트로 확장

    double& rd1 = i;            // Error - 임시값 3.0이 r-value이기 때문에
    double& rd2 = (double)i;    // Error
    double& rd3 = (double&)i;   // OK

    return 0;
}
~~~
* int 객체 i(3)를 double로 타입 변환할 경우
* 임시값(temp) 3.0이 생성된다.
* 그에 비해서 i를 double&로 타입 변환할 경우 메모리 영역을 8 바이트로 확장만 한 뒤 반환한다.

값 타입 변환 : 기본 타입으로 변환하는 것\
참조 타입 변환 : 참조 타입으로 변환하는 것


명시적으로 형변환하면 컴파일러는 위험을 알고도 허용해준다.
* 위험에 대한 책임은 개발자에게 있다.

클래스 간 변환
~~~c++
class CTestA
{
public:
    int m_Test;
};

class CTestB
{
public:
    int m_Test;

    // CTestB(const CTestA &obj) {}
};

int main()
{
    CTestA ta;
    ta.m_Test = 7;

    CTestB tb1 = ta;                                // Error
    CTestB tb2 = (CTestB)ta;                        // Error
    CTestB tb3 = static_cast<CTestB>(ta);           // Error
    CTestB tb4 = reinterpret_cast<CTestB>(ta);      // Error

    CTestB &rtb1 = ta;                              // Error
    CTestB &rtb2 = (CTestB&)ta;                     // OK
    CTestB &rtb3 = static_cast<CTestB&>(ta);        // Error
    CTestB &rtb4 = reinterpret_cast<CTestB&>(ta);   // OK

    return 0;
}
~~~

* 위에서 주석을 해제하면 기본 클래스 변환은 reinterpret_cast를 제외하고는 모두 성공한다.
* 어떤 기준으로 변환해야하는지 컴파일러는 모르기 때문이다.
* reinterpret_cast는 값 타입 변환을 허용하지 않기 때문이다.

참조 타입의 변환인 경우
* C-Style 캐스팅과 reinterpret_cast만 성공한다. - 둘은 모두 강제 타입 변환이다.
* 컴파일러는 참조 타입 변환 시 서로 상관없는 클래스 타입으로는 변환을 허용하지 않기 때문이다.
* static_cast는 상속 관계에서만 변환을 허용한다.

### 6.10.2 상속 관계 클래스 타입 변환
