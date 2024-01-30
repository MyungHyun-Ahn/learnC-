#pragma once


// ���� �������̽�
template<typename RT, typename... ATs>
class CLambdaInterface
{
public:
	RT Call(ATs... args)
	{
		return _Call(args...);
	}

	virtual RT _Call(ATs... args) = 0; // ���� ���� �Լ�
};


// ���ٸ� ������ �����ϴ� Ŭ�����̱� ������ LAMBDA Ÿ���� �ݵ�� �ʿ��ϴ�.
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
class CFunction; // CFunction<T> ���� ����

// CFunction�� �����ϴ� ������ ������ �� �ִ� ���ø� ���ڴ� ���� �Լ��� �ñ״�ó ��
template<typename RT, typename... ATs>
class CFunction<RT(ATs...)>
{
public:
	CFunction()
	{
		m_pLambdaInterface = NULL;
	}

	template<typename LAMBDA>
	CFunction(const LAMBDA &lambda) // ������ Ÿ���� �˷����� ����
	{
		m_pLambdaInterface = new CLambda<LAMBDA, RT, ATs...>(lambda);
	}

	template<typename LAMBDA>
	CFunction<RT(ATs...)> &operator=(const LAMBDA &lambda) // ������ Ÿ���� �˷����� ����
	{
		if (m_pLambdaInterface)
		{
			delete m_pLambdaInterface;
		}

		m_pLambdaInterface = new CLambda<LAMBDA, RT, ATs...>(lambda);
		return *this;
	}

	RT operator() (ATs... args) // �ᱹ CFunction ��ü�� Functor�� �ȴ�.
	{
		return m_pLambdaInterface->Call(args...);
	}

	// CLambda�� �θ� Ŭ�����̹Ƿ� �ڽ� ��ü�� �����͸� ����� �� �ֱ� ����
	CLambdaInterface<RT, ATs...> *m_pLambdaInterface;
};