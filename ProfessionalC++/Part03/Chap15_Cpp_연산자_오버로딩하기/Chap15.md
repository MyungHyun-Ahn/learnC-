# Chapter 15 C++ 연산자 오버로딩하기
## 15.1 연산자 오버로딩 개요
### 15.1.1 연산자 오버로딩을 하는 이유
1. 자신이 정의할 클래스를 기본 타입처럼 다루기 위해
2. 프로그램을 좀 더 세밀하게 제어하기 위해

### 15.1.2 연산자 오버로딩의 한계
1. 연산자 기호를 새로 만들 수 없다.
2. 일부 연산자는 오버로딩할 수 없다.
3. 피연산자의 인수의 개수는 바꿀 수 없다.
4. 연산자의 우선순위는 바꿀 수 없다.
5. 기본 타입 연산자의 의미는 바꿀 수 없다.

### 15.1.3 연산자 오버로딩 선택
operatorX라는 이름의 메서드나 함수를 정의하는 방식으로 정의한다.
* X자리에 오버로딩할 연산자 기호를 적는다.
* operator와 X 사이에는 공백을 넣어도 된다.

연산자를 오버로딩하는 함수나 메서드를 작성할 때의 몇 가지 결정 사항
1. 메서드와 전역함수
   * 반드시 메서드로 정의 : 클래스 문맥을 벗어나면 의미가 없는 연산자
   * 반드시 전역함수로 정의 : 연산자의 좌변에 소속 클래스가 아닌 다른 타입의 변수도 나와야하는 경우
   * 메서드와 전역함수 둘 다 가능 : 특별히 전역함수로 해야하는 경우가 아니라면 메서드로 한다.
2. 인수 타입에 대한 결정사항 : 인수 타입은 선택할 사항이 많지 않다
   * 인수의 개수를 바꿀 수 없기 때문
3. 리턴 타입에 대한 결정사항
   * 마음껏 지정할 수 있다.
4. 동작에 대한 결정사항
   * 마음껏 동작을 구현할 수 있다.

### 15.1.4 오버로딩하면 안 되는 연산자
* 주소연산자 &
* 이항 부울 연산자 && || : C++의 단락 평가 규칙을 적용할 수 없기 때문
* 콤마 연산자 ,


### 15.1.5 오버로딩할 수 있는 연산자
695 page 참고


### 15.1.6 우측값 레퍼런스
* 두 번째 객체가 대입연산 후 삭제될 객체일 때

일반 대입 연산자의 프로토 타입

T& operator=(const T&);

이동 대입 연산자의 프로토 타입

T& operator=(T&&);

대부분의 연산자는 좌측값과 우측값 버전이 둘 다 있어도 상관없다.


### 15.1.7 관계 연산자

bool operator!=(const T& a, const T& b);\
bool operator<(const T& a, const T& b);\
bool operator<>=(const T& a, const T& b);\
bool operator>=(const T& a, const T& b);

## 15.2 산술 연산자 오버로딩 하기
### 15.2.1 단항 뺄셈과 단항 덧셈 연산자 오버로딩하기
단항 뺄셈 : 피연산자의 부호를 바꾼다.
* T operator-() const;

단항 덧셈 : 피연산자를 그대로 반환한다.
* 대체로 항등 연산을 수행한다. - 오버로딩 하지 않는다.


### 15.2.2 증가와 감소 연산자 오버로딩하기
T& operator++(); // 선행 증가\
T operator++(); // 후행 증가\
T& operator--(); // 선행 감소\
T operator--() // 후행 감소;


선행 연산의 리턴값은 피연산자의 최종 결과와 같다.

하지만 후행 연산의 리턴값은 피연산자의 최종 상태와 다르기 때문에 레퍼런스로 리턴할 수 없다.

## 15.3 비트 연산자와 논리 연산자 오버로딩하기
* 표를 보고 참고하자

## 15.4 스트림 입출력 연산자 오버로딩하기

std::ostream& operator<<(std::ostream& ostr, const T& t);\
std::istream& operator>>(std::ostream& istr, T& t);
* 위의 방식으로 오버로딩하면 된다.

## 15.5 인덱스 연산자 오버로딩하기
인덱스 연산자를 오버로딩하려면 임의 접근 기능을 구현해야 한다.

T& operator[](size_t x);

### 15.5.1 읽기 전용 operator[] 만들기
* T& operator[](size_t t); : 읽기와 쓰기 가능
* const T& operator[](size_t t) const; : 읽기만 가능

### 15.5.2 배열의 인덱스가 정수가 아닐 때
* 연관 배열(map 등)에서 정수가 아닌 string 값으로 키 값을 지정 가능하다.
* T& operator[](std::string_view key);
* const T& operator[](std::string_view key) const;

## 15.6 함수 호출 연산자 오버로딩하기
* 클래스의 객체를 함수 객체 또는 펑터(모듈 함수)로 만들 수 있다.
* int operator()(int param);

전역함수보다 함수 객체를 만들었을 때 장점
* 함수 호출 연산자를 여러 번 호출하더라도 정보를 지속적으로 유지할 수 있다.
* 데이터 멤버를 설정하는 방식으로 함수 객체의 동작을 변경할 수 있다.

물론 전역 변수나 static 변수로도 얼마든지 구현할 수 있다.
* 전역 변수나 static 변수는 멀티스레드 환경에서 문제가 발생할 수 있다.


## 15.7 역참조 연산자 오버로딩
*, ->, ->* 또한 오버로딩할 수 있다.
* 역참조 연산자를 오버로딩하면 그 클래스의 객체를 포인터처럼 다룰 수 있다.

### 15.7.1 operator* 구현 방법
포인터를 역참조 한다. : 포인터가 가리키던 메모리에 접근한다.

T& operator*();\
const T& operator*();


### 15.7.2 operator-> 구현 방법
* 화살표 연산자를 적용한 결과는 반드시 객체의 멤버나 메서드여야 한다.

T* operator->();\
const T* operator()->() const;
* C++에서는 오버로딩한 operator-> 에서 리턴한 값에 다른 operator->를 적용한다.
* 그렇기 때문에 반드시 포인터로 리턴하게 오버로딩해야 한다.


## 15.8 변환 연산자 구현하기

operator double() const;


### 15.8.1 명시적 변환 연산자로 모호한 문제 해결하기
생성자 앞에 explicit 키워드를 지정해서 자동변환할 때 이 생성자를 사용하지 않게 할 수 있다.

C++11부터는 생성자 대신 double 변환 연산자를 explicit으로 선언하는 방식으로 해결한다.

explicit operator double() const;


### 15.8.2 부울 표현식으로 변환하기
if (ptr != nullptr) 혹은 if (ptr)을 사용하고 싶을 때

이럴 때 변환 연산자는 주로 void* 타입을 사용한다.

template\<typename T> Pointer\<T>::operator void*() const { return ptr; }
* 위와 같이 void* 변환 연산자를 오버로딩하면 비교 연산도 문제없이 실행된다.

## 15.9 메모리 할당과 해제 연산자 오버로딩하기
### 15.9.1 new와 delete의 구체적인 작동방식

Test *test = new Test();
* new Test() 을 new-표현식이라 부른다.

1. 먼저 operator new를 호출해서 Test 객체에 대한 메모리를 할당하고
2. 객체의 생성자를 호출한다.

delete test;
* delete-표현식이라 부른다.

1. test의 소멸자를 호출한 다음
2. operator delete를 호출해서 test에 할당된 메모리를 해제한다.


operator new, delete를 오버로딩해서 메모리 할당과 해제를 커스터마이징할 수 있다.
* 하지만 생성자와 소멸자를 호출하는 동작은 변경할 수 없다.


new-표현식과 operator new

new-표현식은 여섯 가지다.
1. void *operator new(size_t size); : new
   * 실패시 null이 아닌 std::bad_alloc 예외 발생 - 프로그램이 터진다.
   * try - except로 처리하거나
   * new(noexpt)를 사용한다.
2. void *operator new(size_t size, const std::nothrow_t&) noexcept; : new (noexpt) : 실패시 0 반환
3. 이에 대응하는 [] 버전이 있다.

실제로 객체를 할당하지 않고 객체의 생성자만 호출하는 배치 new-연산자
* 기존에 생성된 메모리에서 객체를 생성한다.
* 메모리 풀을 구현할 때 유용하다.

1. void *operator new(size_t size, void *p) noexcept;
2. void *operator new[](size_t size, void *p) noexcept;

배치 new 연산자는 C++ 표준에서 오버로딩을 금지


delete-표현식과 operator delete
* 직접 호출할 수 있는 delete-표현식 단 두 개(delete, delete[])
* nothrow나 배치 버전은 없다.

배치 버전의 new로는 메모리가 따로 할당되지 않기 때문에 해제할 대상이 없다.