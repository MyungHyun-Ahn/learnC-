# 01. 타입 추론(Type deduction)
## template type deduction
C++11의 auto가 template 타입 추론을 기반으로 동작함
* 즉, template 타입 추론 규칙을 만족하면 auto에 대해서도 만족함

예시
~~~Cpp
// 선언
template<typename T>
void f(const T& param); // ParamType

// 사용
int x = 0;
f(x); // expr
~~~
* 이 경우 T는 int ParamType은 const int& 로 추론됨

T의 추론
* expr의 형식과 ParamType의 형식 모두 의존함

세가지 경우가 존재
* ParamType이 포인터 또는 참조 형식이지만 보편 참조(universal reference)는 아닌 경우
* ParamType이 보편 참조인 경우
* ParamType이 포인터도 아니고 참조도 아닌 경우