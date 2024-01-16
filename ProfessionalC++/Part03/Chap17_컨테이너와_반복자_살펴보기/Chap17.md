# Chapter 17 컨테이너와 반복자 살펴보기
## 17.1 컨테이너 개요
순차 컨테이너
* vector(동적 배열)
* deque
* list
* forward_list
* array

연관 컨테이너
* map
* multimap
* set
* multiset

비정렬 연관 컨테이너(해시 테이블)
* unordered_map
* unordered_multimap
* unordered_set
* unordered_multiset

컨테이너 어댑터
* queue
* priority_queue
* stack


표준 라이브러리 컨테이너는 C++의 string이나 스트림도 어느 정도 지원한다.
* bitset으로 고정된 수의 비트를 저장할 수 있다.

### 17.1.1 원소에 대한 요구사항
표준 라이브러리 컨테이너는 원소를 값으로 처리한다.
* 표준 라이브러리를 사용하는 클래스를 작성할 때는 반드시 복제할 수 있게 만들어야 한다.

원소를 레퍼런스로 처리하고 싶다면 원소에 대한 포인터로 저장한다.
* 컨테이너에서 복제하는 대상은 포인터기 때문에 값은 원본과 똑같은 원소를 가리킨다.

아니면 std::reference_wrapper를 저장해도 된다. \<functional>
* std::ref(), std::cref()로 생성하고
* 결과로 나온 레퍼런스를 복제할 수 있게한다.

이동 전용 타입, 즉 복제할 수 없는 타입도 컨테이너에 저장할 수 있지만
* 컨테이너 연산 일부는 컴파일 에러를 발생시킬 수 있다.

### 17.1.2 익셉션과 에러 검사


### 17.1.3 반복자 iterator
컨테이너의 종류가 달라져도 반복자의 인터페이스는 모두 C++의 표준을 따르기 때문에 동일하다.
* 반복자도 특정 원소에 대한 포인터로 생각할 수 있다.


## 17.2 순차 컨테이너
### 17.2.1 vector
vector는 \<vector> 헤더 파일에 정의된 클래스 템플릿으로 저장할 원소의 타입과 할당자 타입을 매개변수로 받는다.
* template\<class T, class Allocator = allocator\<T>> class vector;

Allocator 매개변수는 클라이언트가 메모리 할당 방식을 커스터마이즈하는 데 사용된다.

고정크기 vector
* vector의 생성자에 원소 수를 지정할 수 있다.
* operator[]를 사용하여 원소에 접근 가능하다.
* at(), front(), back()을 사용해서 원소에 접근하는 것도 가능하다.
* vector에서 원소를 접근하는 연산의 복잡도는 모두 상수 시간이다.

for each 문에서 auto& 처럼 레퍼런스를 받아야 값 수정이 가능하다.


동적 크기 vector
* 크기가 동적으로 조절된다.
* push_back() 메서드로 vector에 추가하면 새로 추가한 원소에 대한 메모리는 vector가 알아서 한다.


vector의 세부 기능

생성자와 소멸자
* vector\<int> intVector(10, 100);
    * 초기값이 100인 int 원소 10개를 담은 vector 생성
    * 디폴트 값을 지정하지 않으면 모두 0으로 초기화한다.
* vector\<int> intValue({1, 2, 3, 4});
  * 원소를 이니셜라이저 리스트로 지정해도 된다.
* vector\<int> intVector = {1, 2, 3, 4, 5};
  * 유니폼 초기화도 사용할 수 있다.
* auto elementVector = make_unique\<vector\<Element>>(10);
  * 벡터를 힙에다 할당할 수 있다.

vector의 복제와 대입
* 저장된 값을 모두 삭제하고 원하는 값을 추가하는 assign() 메서드
  * intVector.assign(5, 100);
  * 원래 원소를 모두 삭제하고 100 5개 추가

* 두 vector의 원소를 상수시간에 바꾸는 swap() 메서드
  * vectorOne.swap(vectorTwo);

vector 비교
* ==, !=, <, >, <=, >= 여섯개의 연산자를 지원한다.
* 클래스의 객체를 저장한 경우 연산자 오버로딩이 되어 있어야 한다.


vector 반복자
* vector\<int>::iterator iter = begin(intVector);
  * begin은 컨테이너의 첫 번째 원소를 참조하는 반복자를 반환한다.

* iter != end(intVector);
  * vector의 마지막 원소를 지났는지 비교한다.

가능하면 선행 증가를 지정하는 것이 좋다.
* iter++는 반드시 새로운 반복자 객체를 리턴하고
* ++iter는 iter에 대한 레퍼런스만 리턴된다.

원소 객체의 필드에 접근하기
* iterator에 -> 연산자를 적용하면 그 객체의 메서드를 호출하거나 데이터 멤버에 접근 가능하다.

const_iterator
* 읽기 전용이다.
* 반복자가 참조하는 원소를 수정할 수 없다.
* auto를 사용하는 경우 cbegin()이나 cend()를 호출해야 한다.

반복자의 안전성
* end()가 가리키는 반복자는 마지막 원소가 아닌 그 다음 원소이다.
* end()의 리턴값을 역참조하면 예상과 다른 결과가 나온다.

마이크로소프트 비주얼 C++는 기본적으로 디버그 모드에서 문제를 발견하면 assertion error를 발생시킨다.
* 릴리스 모드의 경우 아무런 검증 작업을 수행하지 않는다.

반복자의 다른 연산
* 랜덤 엑세스를 지원한다.

반복자와 인덱싱
* vector의 원소에 대해 반복하는 for문을 인덱스 변수와 size() 메서드만으로 간단히 작성할 수 있다면 반복자는 굳이 필요하지 않다.

다음 작업의 경우에는 반복자를 사용하는 것이 유리하다.
1. 컨테이너의 원하는 지점에 추가 삭제가 유리하다.
2. 표준 라이브러리의 알고리즘을 사용하기 쉽다.
3. 순차적으로 접근할 때는 인덱스로 원소를 하나씩 조회하는 것보다 반복자를 사용하는 것이 효율적이다.
   * vector에 한해서는 그렇지 않을 때도 있지만 list, map, set의 경우에는 반복자가 항상 빠르다.

vector에 레퍼런스 저장하기
* \<functional> 헤더파일의 std::reference_wrapper로 감싸서 저장한다.
* vector\<reference_wrapper\<string>> vec{ref(str1)};
* vec.push_back(ref(str2));
* vec[1].get() += "!"; // 이렇게 하면 두 번째 레퍼런스가 참조하는 string 값을 변경


원소 추가와 삭제
* 추가 push_back
* 삭제 pop_back
  * 삭제한 원소를 리턴하지 않는다.
  * back 메서드로 미리 받아둔다.

vector에서 제공하는 insert 메서드를 이용하면 원하는 지점에 원소를 추가할 수 있다.
* 뒤의 원소는 모두 밀려난다.

insert는 오버로딩된 버전이 있다.
* 원소 1개만 추가
* 원소 1개에 대한 n개의 복제본을 추가
* 반복자의 범위로 지정된 원소들을 추가
* 이동의미론 적용
* 초기화 리스트에 지정하여 vector에 추가

erase 메서드를 사용하면 원하는 원소를 삭제할 수 있다.


임플레이스 연산
* emplace_back() 메서드
* 복제나 이동 작업을 수행하지 않고 컨테이너에 공간을 마련해서 객체를 그 자리에 바로 생성한다.
* C++17 부터 추가된 원소에 대한 레퍼런스를 반환한다.

반복자를 사용해 연산이 끝난 뒤에는 자동으로 갱신되지 않는다.
* 프로그래머가 적절히 대응해주어야 한다.

vector의 메모리 할당 방식
* vector는 원소를 연속된 메모리 공간에 저장한다.
* 공간이 모자르다면 더 큰 공간을 할당받아 기존 원소를 이동시킨다.
* 복사의 비용이 크기 때문에 필요한 양보다 더 큰 공간을 할당받는다.

vector의 메모리 메커니즘을 알아야 하는 이유
1. 효율성 : 원소 추가시 선형 시간의 복잡도를 가질 수 있다.
2. 반복자 무효화 : 메모리 재할당이 발생하면 기존의 반복자가 무효가 된다.

크기와 용량
* size() : 현재 vector에 담긴 원소의 수
* capacity() : 재할당 없이 담을 수 있는 원소의 수
* capacity() - size() : 현재 상태에서 재할당 없이 담을 수 있는 원소의 수

예비 용량
* reserve() : 미리 원소를 담을 공간을 확보 가능

데이터에 직접 접근하기
* vector에서 data() 메서드를 호출하면 vector의 데이터가 있는 메모리 블록을 포인터로 받을 수 있다.


### 17.2.3 deque
* 원소를 메모리에 연속적으로 저장하지 않는다.
* 양 끝에 삽입 삭제 완벽히 상수시간에 처리한다.
* vector에는 없는 push_front, pop_front, emplace_front 메서드를 제공한다.
* 앞이나 뒤에 원소를 추가해도 반복자를 무효화하지 않는다.
* reserve, capacity 같은 메모리 관리 메서드를 제공하지 않는다.


### 17.2.4 list
* 양방향 연결 리스트를 구현한 표준 라이브러리이다.
* 모든 지점에 삽입 삭제는 상수시간이지만
* 조회 작업은 선형 시간이다.
* 반복자로만 개별 원소에 접근 가능하다.

원소 접근 연산
* front와 back만 지원한다.
* 나머지 원소는 반복자로만 접근 가능하다.

반복자
* 양방향으로 접근한다.
* 랜덤 액세스는 지원하지 않으므로 반복자끼리의 산술 연산은 불가능하다.
* it++, ++it와 같은 연산으로만 원소를 탐색할 수있다.

원소의 추가와 삭제 연산
* push_back, pop_back, emplace, emplace_back, erase, clear 등이 있다.

list 크기에 관련된 연산
* size, empty, resize는 제공하지만
* reserve, capacity와 같은 메서드는 제공하지 않는다.

list의 특수 연산
* splice : 리스트끼리 이어붙이기


## 17.3 컨테이너 어댑터
내부적으로 순차 컨테이너를 사용하여 구현된다.
* 여러 원소를 동시에 추가/삭제하는 기능이나 반복자는 제공하지 않는다.

### 17.3.1 queue
* 표준 FIFO 방식을 구현한 것이다.
* 
template\<class T, class Container = deque\<T>> class queue;
* 두 번째 템플릿 매개변수로 deque나 list 중 사용할 수 있다.

queue 연산
* push, emplace : 큐의 끝에 원소를 추가
* pop : 맨 앞의 원소를 제거
* front, back : 맨 앞과 맨 뒤의 원소 조회

### 17.3.2 priority_queue
* 우선순위 큐 : 원소를 정렬된 상태로 저장하는 큐
* \<queue> 헤더에 정의되어 있다.

template \<class T, class Container = vector\<T>, class Compare = less\<T>>;
* 두 번째 템플릿 매개변수로는 vector, deque 사용가능
* 세번째는 operator< 연산으로 T 타입끼리의 비교

priority_queue 연산
* push, emplace 추가
* pop 삭제

### 17.3.3 stack
* FILO, LIFO

template\<class T, class Container = deque\<T>> class stack;
* vector, list 사용가능



## 17.4 정렬 연관 컨테이너
* 원소를 키와 값의 쌍으로 저장한다.
* map, multimap, set, multiset
* 각각의 원소를 트리 형태의 데이터 구조에 정렬된 상태로 저장

### 17.4.1 pair 유틸리티 클래스
* \<utility> 헤더에 정의
* pair는 두 값을 그룹으로 묶는 클래스 템플릿이다.
* pair에 정의된 ==과 <는 비교하려는 두 값을 모두 비교한다.
* make_pair라는 유틸리티 함수 템플릿도 있다.
* make_pair는 명시적으로 타입을 지정하지 않아도 타입을 추론할 수 있다.


### 17.4.2 map
* 단일 값이 아닌 키와 값의 쌍으로 저장한다.
* 추가, 조회, 삭제 연산 모두 키를 기준으로 수행한다.
* operator< 연산자를 커스터마이징해서 우선순위를 정할 수 있다.
* 대체로 레드블랙트리와 같은 균형트리로 구현된다.

map 생성하기
* 키 타입, 값 타입, 비교 타입, 할당자 타입이라는 네 가지 타입을 매개변수로 받는다.

원소 추가하기
* map은 새로 추가할 원소의 위치를 내부적으로 결정하기 때문에 키와 값만 지정하면 된다.
* map의 키는 중복되면 안된다.
* 키가 같은 값을 넣고 싶다면 vector나 array와 같은 다른 컨테이너로 저장하는 것
* 혹은 multimap을 사용하면 된다.

insert 메서드
* insert 메서드로 map에 원소를 추가하면 키가 이미 존재하는지 검사할 수 있다.
* pair 혹은 initializer_list로 지정해야 한다.
* insert 메서드의 기본 버전은 iterator와 bool 원소로 구성된 pair를 반환한다.
* bool 원소는 성공 여부, iterator 원소는 지정한 키에 대한 값을 가리킨다.

insert_or_assign 메서드
* insert와는 다르게 값을 덮어씌운다.
* 또한 키와 값에 대한 매개변수를 따로 받는다.

operator[]
* map에 값을 추가한다.
* 값이 이미 있으면 덮어씌운다.

map의 반복자
* 양방향으로 작동한다.
* iter->second.getValue(); : 로 값에 접근한다.

find 메서드로 원하는 키에 대한 iterator를 반환받을 수 있다.


원소 삭제하기
* erase(키) 메서드로 원소를 삭제할 수 있다.
* 주어진 키와 일치하는 원소를 삭제한다.


### 17.4.3 multimap
* 한 키에 여러 개의 값을 담을 수 있는 map
* 유니폼 초기화를 지원

map과 다른 점
* operator[]와 at()을 제공하지 않는다.
* 원소를 추가하는 연산은 항상 성공한다. insert() 메서드는 iterator 하나만 리턴한다.
* insert_or_assign()과 try_emplace() 메서드를 제공하지 않는다.

find() 메소드
* 지정된 키에 해당하는 모든 원소를 참조하는 iterator를 리턴한다.
  * 주어진 키에 대해 첫 번째 원소가 아닐수도 있다.

multimap에서는 같은 키에 속한 원소의 범위를 가리키는 iterator를 리턴하는 메소드를 지원한다.
* lower_bound, upper_bound
* 각각 첫 번째와 마지막 바로 뒤에 있는 반복자를 리턴한다.
* 해당 키에 대한 값이 없다면 두 값은 같다.
* equal_range() 메서드는 두 값을 pair로 묶어서 리턴한다.


### 17.4.4 set
* map과 상당히 비슷하다.
* set은 그러나 키가 곧 값이다.
* 키를 따로 갖지않고 정보를 중복되지 않게 정렬해서 저장하고
* 추가, 조회, 삭제 연산 또한 빠르다.

map과 다른 점
* operator[], insert_or_assign, try_emplace를 제공하지 않는다.

### 17.4.5 multiset
* multimap과 map의 관계와 같다.
* set에서 지원하는 메소드는 모두 지원한다.
* 같은 원소를 가질 수 있다.


## 17.5 비정렬 연관 컨테이너(해시 테이블)
* 원소를 정렬하지 않는다.

### 17.5.1 해시 함수
* 비정렬 연관 컨테이너를 해시 함수로 구현하기 때문에 흔히 해시 테이블이라 부른다.
* 해시 테이블은 버킷이라 부르는 배열 형태로 원소를 저장한다.
* 해시 함수는 키를 해시값으로 변환하는데 이 값은 다시 버킷 인덱스로 변환된다.
* 이렇게 버킷 인덱스로 표현된 키에 대응되는 값을 해당 버킷에 저장한다.

해시 함수의 결과는 중복될 수 있다.
* 두 개 이상의 키가 같은 버킷 인덱스를 가리키는 상황을 해시 충돌이라 부른다.

기존 map에 비해 해시 테이블에 대한 조회 연산은 굉장히 빠르다.
* 하지만 충돌 발생 횟수에 따라 성능이 달라질 수 있다.

충돌이 전혀 없는 해시 함수를 완전 해시라고한다.
* 완전 해시의 조회시간은 상수 시간이다.
* 일반 해시의 조회시간은 평균적으로 1에 가깝다.


### 17.5.2 unordered_map
\<unordered_map> 헤더 파일에 클래스 템플릿으로 정의돼 있다.

template\<class Key,\
class T,\
class Hash = hash\<key>,\
class Pred = std::equal_to\<Key>,\
class Alloc = std::allocator\<std::pair\<const Key, T>>>\
class unordered_map;
* 키 타입, 값 타입, 해시 타입, 등호 비교 타입, 할당자 타입

### 17.5.3 unordered_multimap
### 17.5.4 unordered_set, unordered_multiset