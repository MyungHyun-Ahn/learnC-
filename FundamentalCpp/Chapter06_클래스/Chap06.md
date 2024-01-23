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