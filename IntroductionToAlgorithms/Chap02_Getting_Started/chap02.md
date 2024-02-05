# Chapter02 Getting Started

## 2.1 Insertion sort (삽입 정렬)
Input : n 개의 숫자\
Output : 정렬된 n 개의 숫자

* 정렬하려는 숫자를 Keys라고도 함
* 일반적으로 n 개의 숫자들은 n 개의 요소를 가진 배열로 제공됨

책에서는 "pseudocode"라는 의사 코드를 제공함
* 다양한 프로그래밍 언어로 표현될 수 있다.


pseudocode?
* 가장 명확하고 간결한 표현 방법
* 때때로는 가장 명확한 표현 방법이 English일 수 있다.
* 간결하게 표현하기 위해 추상화, 모듈화, 에러 제어 등이 생략될 수 있다.

작은 수의 정렬에 효과적으로 사용될 수 있는 Insertion Sort

Insertion Sort - Pseudo Code
* 정렬해야 하는 수는 A라는 배열의 형태로 제공
~~~
for j = 2 to A.length
    key = A[j] // 정렬된 A[1..j-1]에 A[j]를 삽입
    i = j - 1
    while i > 0 and A[i] > key
        A[i + 1] = A[i]
        i = i - 1
    A[i + 1] = key
~~~


C++ Insertion Sort 구현 코드
~~~C++
void InsertionSort(int *arr, int arrSize)
{
	for (int j = 1; j < arrSize; j++)
	{
		int key = arr[j];
		int i = j - 1;
		while (i >= 0 && arr[i] > key)
		{
			arr[i + 1] = arr[i];
			i--;
		}

		arr[i + 1] = key;
	}
}
~~~

루프 불변성에 대해 증명 - 만족 시켜야할 3가지
* Initialization : 첫 번째 반복 이전에 true
* Maintenance : 반복 이전에 true 였다면 다음 반복 이전까지 true를 유지
* Termination : 루프가 끝나면 알고리즘이 정확하게 끝났다는 속성을 제공

정확성을 보이기 위해 루프 불변성을 사용한다.
* 일반적으로 루프가 종료되는 조건과 함께 루프 불변성을 제공

Pseudocode Convention - 의사코드 규칙
* 들여쓰기는 블록 구조를 의미
* 반복 구문의 의미는 다른 프로그래밍 언어와 유사 (while, for, if-else ...)
* //는 주석
* i = j = e : i와 j에 e를 할당
* 변수는 지정된 procedure에 지역적, 명시적인 표시없이 전역변수를 사용하지 않음
* 배열 이름과 대괄호를 통해 배열 요소에 접근
* 복합 데이터를 objects라고함, dot(.)을 통해 각 요소에 접근
  * 배열이나 객체를 나타내는 변수를 포인터로 취급
  * 때때로는 포인터가 객체를 가리키지 않을 수도 있다. NIL
* 매개변수를 값으로 전달, 객체를 전달하는 경우, 객체는 복사되지만 요소는 그렇지 않음
* return문은 호출 전 제어문으로 돌아감. caller에게 값 전달을 목적으로도 사용
* and 와 or 연산자는 short-circuiting(단락), x and y - x를 먼저 평가하고, x가 false라면 y는 평가하지 않음
* error 키워드는 호출된 procedure의 조건이 잘못되었음을 의미