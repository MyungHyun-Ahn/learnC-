# 03 - 자원 관리
## 항목 13: 자원 관리에는 객체가 그만!
smart pointer

자원 관리에 객체를 사용하는 방법의 두 가지 특징
* 자원을 획득한 후에 자원 관리 객체에게 넘김
  * 자원 획득 즉 초기화(Resource Acquisition Is Initalization) 패턴
* 자원 관리 객체는 자신의 소멸자를 사용해서 자원이 확실히 해제되도록 함

일반적으로 널리 쓰이는 RAII 객체는
* std::shared_ptr

## 항목 14: 자원 관리 클래스의 복사 동작에 대해 진지하게 고찰하자
RAII 객체가 복사된다면?

다음의 선택지
* 복사를 금지
* 관리하고 있는 자원에 대해 참조 카운팅을 수행
* 관리하고 있는 자원도 진짜로 복사
* 관리하고 있는 자원의 소유권을 옮김

## 항목 15: 자원 관리 클래스에서 관리되는 자원은 외부에서 접근할 수 있도록 하자
* 암시적 변환 혹은 명시적 변환을 통해 그 클래스가 관리하는 자원을 얻을 수 있도록 해야함

## 항목 16: new 및 delete를 사용할 때는 형태를 반드시 맞추자

## 항목 17: new로 생성한 객체를 스마트 포인터에 저장하는 코드는 별도의 한 문장으로 만들자
std::shared_ptr\<Object> sPtr(new Object);
* 이렇게 하지 않으면 예외가 발생될 때 디버깅하기 힘든 자원 누출 초래 가능