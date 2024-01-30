#pragma once


// 람다 인터페이스
template<typename RT, typename... ATs>
class CLambdaInterface
{
public:
	RT Call(ATs... args)
	{
		return _Call(args...);
	}

	virtual RT _Call(ATs... args) = 0; // 내부 가상 함수
};


// 람다를 실제로 저장하는 클래스이기 때문에 LAMBDA 타입이 반드시 필요하다.
template<typename LAMBDA, typename RT, typename... ATs>
class CLambda : public CLambdaInterface<RT, ATs...>
{
public:
	CLambda(const LAMBDA &lambda)
	{
		m_pLambda = new LAMBDA(lambda);
	}

	~CLambda()
	{
		if (m_pLambda)
		{
			delete m_pLambda;
		}
	}

	virtual RT _Call(ATs... args)
	{
		return (*m_pLambda)(args...);
	}
	
	LAMBDA *m_pLambda;
};


template<typename T>
class CFunction; // CFunction<T> 전방 선언

// CFunction을 정의하는 시점에 전달할 수 있는 템플릿 인자는 오직 함수의 시그니처 뿐
template<typename RT, typename... ATs>
class CFunction<RT(ATs...)>
{
public:
	CFunction()
	{
		m_pLambdaInterface = NULL;
	}

	template<typename LAMBDA>
	CFunction(const LAMBDA &lambda) // 람다의 타입이 알려지는 순간
	{
		m_pLambdaInterface = new CLambda<LAMBDA, RT, ATs...>(lambda);
	}

	template<typename LAMBDA>
	CFunction<RT(ATs...)> &operator=(const LAMBDA &lambda) // 람다의 타입이 알려지는 순간
	{
		if (m_pLambdaInterface)
		{
			delete m_pLambdaInterface;
		}

		m_pLambdaInterface = new CLambda<LAMBDA, RT, ATs...>(lambda);
		return *this;
	}

	RT operator() (ATs... args) // 결국 CFunction 객체는 Functor가 된다.
	{
		return m_pLambdaInterface->Call(args...);
	}

	// CLambda의 부모 클래스이므로 자식 객체의 포인터를 대신할 수 있기 때문
	CLambdaInterface<RT, ATs...> *m_pLambdaInterface;
};