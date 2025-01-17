# Chapter 09 클래스와 객체 마스터하기
## 9.1 friend
C++는 클래스 안에서 다른 클래스나 다른 클래스의 멤버 함수, 비멤버 함수를 friend로 선언하는 기능을 제공한다.
* friend로 지정한 대상은 이 클래스의 protected나 private 멤버와 메서드에 접근할 수 있다.

friend class Bar;

Bar에 있는 메서드 중 특정한 메서드만 프렌드로 만들 수 있다.

friend void Bar::processFoo(const Foo& foo);

클래스 외에 독립 함수도 프렌드로 지정할 수 있다.

friend void dumpFoo(const Foo& foo);

프렌드로 지정할 클래스, 메서드, 함수는 반드시 접근할 클래스 안에서 지정해야 한다.
* 이 기능을 너무 많이 사용하면 캡슐화 원칙이 깨진다.
* 꼭 필요할 때만 사용하자

## 9.2 객체에 동적 메모리 할당하기
### 9.2.2 소멸자로 메모리 해제하기
객체 안에서 동적으로 할당한 메모리는 그 객체의 소멸자에서 해제하는 것이 바람직하다.
* 소멸자는 기본적으로 익셉션이 발생하지 않으며 noexcept 가 적용된다.

noexcept가 적용된 함수에서 except가 발생하면 프로그램이 멈춘다.


### 9.2.3 복제와 대입 처리하기
포인터와 같은 기본 타입에 대해서는 비트 단위 복제, 얕은 복제 혹은 대입이 적용된다.
* 즉 원본 객체의 데이터 멤버를 대상 객체로 단순히 복제하거나 대입하기만 한다.
* 포인터의 경우 복사할 경우 내부 데이터까지 복제되지 않는다.

올바른 메모리를 가리키지 않는 포인터를 댕글링 포인터라 한다.

따라서 대입 연산자에서는 반드시 깊은 복제를 적용해야 한다.
* 메모리를 따로 생성하고 그곳에 복사를 하자.

### 9.2.4 이동 의미론으로 이동 처리하기
객체에 이동 의미론을 적용하려면 이동 생성자와 이동 대입 연산자를 정의해야 한다.
* 메모리를 비롯한 리소스의 소유권을 다른 객체로 이동시키는 것
* 얕은 복제와 비슷하다.
* 소유권을 전환함으로 댕글링 포인터나 메모리 누수를 방지한다.

우측값 레퍼런스
1. 좌측값(lvalue) : 변수처럼 이름과 주소를 가진 대상
2. 우측값(rvalue) : 리터럴, 임시 객체, 값처럼 좌측값이 아닌 모든 대상

우측값 레퍼런스 : 우측값에 대한 레퍼런스
* 우측값이 임시객체일 때 적용되는 개념

함수의 매개변수에 &&를 붙여 우측값 레퍼런스로 만들 수 있다.
* 소유권을 아예 함수로 넘겨버리는 것

이름 있는 변수는 좌측값이다.

이동 의미론 구현 방법
* 이동 의미론은 우측값 레퍼런스로 구현한다.
* 이동 생성자와 이동 대입 연산자를 구현해야 한다.
* 반드시 noexcept로 설정해서 절대로 익셉션이 발생하지 않는다고 컴파일러에 알려줘야 한다.

이동 의미론은 원본 객체를 삭제할 때만 유용하다.

클래스에서 동적 할당 메모리를 사용하는 코드를 작성했다면
* 소멸자, 복제 생성자, 이동 생성자, 복제 대입 연산자, 이동 대입 연산자를 반드시 구현한다.
* 이를 5의 규칙이라 부른다


### 9.2.5 영의 규칙
* 5의 규칙의 멤버 함수를 구현할 필요가 없도록 클래스를 디자인 하는 것


## 9.3 메서드의 종류
### 9.3.1 static 메서드
* 특정 객체 단위가 아닌 클래스 단위로 적용되는 메서드이다.
* this 포인터를 가질 수 없으므로 어떤 객체의 non-static 멤버에 접근할 수 없다.
* 같은 클래스 안에서는 static 메서드를 일반 함수처럼 호출할 수 있다.

### 9.3.2 const 메서드
* 값이 바뀌지 않는 객체를 의미한다.
* 그 객체의 데이터 멤버를 절대로 변경하지 않는 메서드만 호출할 수 있다.
* 즉 객체 내부의 데이터를 변경하지 않겠다는 것이다.
* 객체를 const로 선언하면 const 메서드만 호출할 수 있다.

double getValue() const; 
* 위와 같이 선언하면 const 메서드가 된다.

mutable 데이터 멤버
* mutable size_t mNumAccess = 0;
* 위와 같이 선언하면 mutable 데이터 멤버로 const 메서드에서 값을 변경할 수 있다.

### 9.3.3 메서드 오버로딩
* 매개변수만 다르게 함수나 메서드를 여러 개 정의 하는 것
* 메서드의 리턴 타입에 대한 오버로딩은 지원하지 않는다.

const 기반 오버로딩
* const를 기반으로 오버로딩할 수 있다.
* const 객체에서 이 메서드를 호출하면 const
* non-const 객체에서 호출하면 non-const 메서드로 실행된다.


const 버전과 non-const 버전의 구현 코드가 같을 때
* const_cast() 패턴을 적용한다.
* const 버전은 예전대로 구현하고
* non-const 버전은 const 버전을 적절히 캐스팅해서 호출하는 방식으로 구현

return const_cast\<Test&>(std::as_const(*this).getCellAt(x, y));
* const_cast는 const나 volatile 잠깐 제거하는데 사용한다.
* as_const는 객체에 const 속성을 부여한다. : C++17 미만의 버전은 static_cast를 사용한다.

명시적으로 오버로딩 제거하기

void foo(double i) = delete;
* 위와 같이 선언하면 foo 함수에 인자로 double 타입이 들어오면 컴파일 에러가 발생한다.

### 9.3.4 인라인 메서드
* 인라이닝(inlining) : 메서드를 별도의 코드 블록에 구현해서 호출하지 않고 메서드를 호출하는 부분에서 곧바로 구현 코드를 작성하는 방법

정의부 앞에 inline 키워드를 지정하면 인라인 메서드가 된다.
* 그럼 컴파일러는 함수 호출로 처리하지 않고 함수의 본문을 곧바로 집어넣는다.
* 컴파일러는 inline 키워드를 참고만하고, 성능에 문제될 것 같으면 그냥 무시할 수도 있다.

인라인 메서드는 호출하는 코드에서 반드시 이를 정의하는 코드를 볼 수 있어야 한다.
* 반드시 프로토타입과 구현 코드를 헤더 파일에 작성한다.
* 고급 C++ 컴파일러에서는 그렇게 하지 않아도 된다.

### 9.3.5 디폴트 인수
함수나 메서드에서 매개변수의 기본값을 지정할 수 있다.
* 오른쪽 끝의 매개변수부터 중간에 건너뛰지 않고 연속적으로 나열해야 한다.

모든 매개변수가 디폴트 값이 지정된 생성자는 디폴트 생성자처럼 쓸 수 있다.

## 9.4 데이터 멤버의 변수
### 9.4.1 static 데이터 멤버
static 데이터 멤버 : 전역 변수와 비슷하지만 속한 클래스 범위를 벗어날 수 없다.
* 기본적으로 0으로 초기화 된다.
* 명시적으로 0으로 표기해줘도 된다.

인라인 변수 : C++17

static inline size_t sCounter = 0;
* 이렇게 선언하면 소스 파일에 다음과 같이 적지 않아도 된다.
* size_t AAA::sCounter;

클래스 메서드에서 static 데이터 멤버 접근하기
* 클래스 메서드 안에서는 static 데이터 멤버를 일반 데이터 멤버인 것처럼 사용한다.

const static 데이터 멤버
* 특정 클래스에만 적용되는 상수를 정의할 때는 반드시 static const 데이터 멤버로 선언한다.

비정적 데이터 멤버도 const로 선언할 수 있다.
* const 데이터 멤버에는 어떤 값도 대입할 수 없기 때문에 반드시 생성자에서 초기화해야 한다.
* 이 때문에 비정적 const 데이터 멤버를 가진 클래스에 대입 연산자를 제공하지 못할 수도 있다.
* 이 경우 대입 연산자를 delete 한다.

## 9.5 중첩 클래스
클래스 내부에 구조체, 타입 앨리어스, 열거 타입도 선언할 수 있다.

## 9.6 클래스에 열거 타입 정의하기
클래스 안에서 상수를 여러개 정의할 때는 열거 타입을 활용하는 것이 좋다.


## 9.7 연산자 오버로딩
객체에 대해 연산을 수행할 때가 많다.
* 이 때 연산자 오버로딩을 통해 연산자를 재정의할 수 있다.