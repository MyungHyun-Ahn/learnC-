## The one definition rule (ODR)
* 파일 내에서 함수, 변수, 타입, 템플릿은 오직 단 1개의 정의만 있어야 한다.
  * 컴파일 에러
* 프로그램 내에서 함수나 변수는 단 하나의 정의만 가져야 한다.
  * 링커 에러
* 다른 파일에서는 타입, 템플릿, inline 함수, inline 변수는 중복 정의될 수 있다.
  * 원하지 않은 동작

식별자는 같지만 매개변수가 다르다면 ODR을 위반하지 않는다.
* 함수 오버로딩

## Naming Collisions and an introduction to namespaces
C++의 모든 식별자는 모호한 이름을 가질 수 없다.
* 구분할 수 없다면 링커나 컴파일러에서 에러
* 이 에러를 naming collision이나 naming conflict라고 함


naming conflict가 밠생하는 상황
* 프로그램 내에서 두 개 이상의 같은 이름의 함수가 존재하면 - 링커 에러
* 같은 소스파일 내에서 두 개 이상의 같은 이름의 함수가 존재하면 - 컴파일 에러

