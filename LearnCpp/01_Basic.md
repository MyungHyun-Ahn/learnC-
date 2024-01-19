# 01 Basic

## 1.4 Variable assignment and initialization

### Variable assignment : 변수 할당
int a;\
a = 5;
1. Variable Define
2. Assign the value

2단계로 나눠 수행됨

두가지 과정은 합쳐질 수 있다.

Initialization

int a;
* Default initialization : 불확실한 값이 들어갈 수 있다.

int b = 5;
* copy initialization
* 복잡한 유형에 대해 다른 초기화 방식보다 효율이 떨어짐

int c(6);
* Direct Initialization
* 복잡한 객체를 초기화하기 위해 도입 (클래스 등)
* Modern C++에서 list initialization으로 대체됨
* list ialization에 몇 가지 단점 때문에 쓰기도 한다.
* Direct Initialization은 다른 타입으로 명시적 캐스팅할 때도 쓴다.
* 단점은 변수와 함수를 헷갈리게 만듬

### List initialization methods (C++11)

int d { 5 };\
int e = { 6 };\
int f {}; 

* mordern C++에서 사용하는 것
* 일관된 초기화 구문을 제공하기 위해 도입됨

축소 변환을 허용하지 않음
* int a {4.5}; // 컴파일 에러
* 복사 혹은 직접 초기화는 .5를 날리고 4를 저장함

### 값 초기화와 0 초기화

int x {};
* 위와 같이 초기화하면 value initialization 발생
* 0 으로 초기화

{0} vs {}
* 명시적으로 값을 사용해야할 때 {0}
* 값이 임시이고 교체될 경우 {}

### 사용하지 않는 초기화 변수 경고 Unused initialized variables warnings
Modern 컴파일러에서는 변수가 초기화 되고 사용하지 않으면 경고를 발생

C++17 [[maybe_unused]] attribute
* 사용되지 않을 수도 있다고 컴파일러에게 알리는 것

[[maybe_unused]] double pi {3.141592};


## Introduction to iostream::cout, cin, and endl


### std::cout
* 콘솔에 즉시 출력되지 않고 버퍼에 저장된다.
* 버퍼가 flushed 되면 그제서야 목적지로 보낸다.
* 버퍼가 flush 되기 전에 프로그램이 종료되면 콘솔에 출력되지 않을 수 있음


### std::endl vs '\n'
std::endl는 비효율적일 수 있다.
1. 커서를 다음줄로 이동시킨다.
2. 버퍼를 flush한다. 2번 과정이 일어남
3. 시스템이 자체 flush하도록 유도하는 것이 좋은 방법

'\n'
* 커서를 다음줄로 옮길 뿐 flush 하지 않는다.



