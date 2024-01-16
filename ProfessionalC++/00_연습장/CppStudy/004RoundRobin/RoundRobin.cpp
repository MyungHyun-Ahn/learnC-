#include <iostream>
#include <vector>
#include <string_view>

template<typename T>
class RoundRobin
{
public:
	// 효율을 위해 원소의 예상 개수를 클라이언트로부터 받는다.
	RoundRobin(size_t numExpected = 0);
	virtual ~RoundRobin() = default;

	RoundRobin(const RoundRobin &src) = delete;
	RoundRobin &operator=(RoundRobin &rhs) = delete;


	// 리스트의 끝에 원소를 추가한다.
	void add(const T &element);

	// operator== 연산자를 호출한 결과
	// 똑같다고 판단된 첫 번째 원소만 삭제한다.
	// getNext() 사이에 호출될 수 있다.
	void remove(const T &element);

	// 리스트의 다음번 원소를 리턴한다.
	// 첫 번째 원소부터 시작해서 마지막 원소에 다다르면 다시 첫 번째 원소로 돌아온다.
	// 이때 중간에 추가되거나 삭제한 원소도 반영한다.
	T &getNext();

private:
	std::vector<T> mElements;
	// 하나 이상의 템플릿 매개변수로 정의한 타입에 접근할 때는 항상 typename 키워드를 지정해야 한다.
	typename std::vector<T>::iterator mCurrentElement;
};

template<typename T>
RoundRobin<T>::RoundRobin(size_t numExpected)
{
	mElements.reserve(numExpected);
	mCurrentElement = begin(mElements);
}

template<typename T>
void RoundRobin<T>::add(const T &element)
{
	// 원소를 마지막에 추가하더라도 push_back()을 호출한 결과로
	// vector가 재할당돼서 반복자가 무효화될 수 있다.
	// 공간을 절약하려면 반복자의 랜덤 액세스 기능을 최대한 활용한다.
	int pos = mCurrentElement - begin(mElements);
	mElements.push_back(element);
	mCurrentElement = begin(mElements) + pos;
}

template<typename T>
void RoundRobin<T>::remove(const T &element)
{
	for (auto it = begin(mElements); it != end(mElements); ++it)
	{
		if (*it == element)
		{
			// 반복자가 참조하는 원소가 삭제할 대상의 다음 원소를 가리키고 있을 때 원소를 삭제하면 반복자가 무효화 된다.
			// 삭제한 후 현재 원소의 위치를 관리하려면 반복자의 랜덤 액세스 기능을 활용한다.
			int newPos;

			if (mCurrentElement == end(mElements) - 1 && mCurrentElement == it)
			{
				// 반복자가 리스트의 마지막 원소를 가리키는 상태에서
				// 그 원소를 삭제하려 하므로 다시 첫 번째 원소의 위치로 이동시킨다.
				newPos = 0;
			}
			else if (mCurrentElement <= it)
			{
				// 그렇지 않고 mCurrentElement가 삭제하려는 원소나
				// 그 앞의 원소를 가리키고 있다면 위치는 변하지 않는다.
				newPos = mCurrentElement - begin(mElements);
			}
			else
			{
				// 두 경우 모두 해당되지 않는다면
				// 한 칸 앞이 새 위치가 된다.
				newPos = mCurrentElement - begin(mElements) - 1;
			}

			// 원소를 삭제한다. (리턴 값은 무시)
			mElements.erase(it);

			// 반복자가 유효한 상태를 유지하도록 리셋한다.
			mCurrentElement = begin(mElements) + newPos;

			return;
		}
	}
}

template<typename T>
T &RoundRobin<T>::getNext()
{
	// 가장 먼저 원소가 담겨있는지 먼저 확인한다.
	if (mElements.empty())
		throw std::out_of_range("No elements in the list");

	auto &toReturn = *mCurrentElement;

	// 반복자를 원소 수에 대한 모듈로 연산을 이용하여 증가시킨다.
	++mCurrentElement;
	if (mCurrentElement == end(mElements))
		mCurrentElement = begin(mElements);

	return toReturn;
}

class Process final
{
public:
	Process(std::string_view name) : mName(name) {}

	void doWorkDuringTimeSlice()
	{
		std::cout << "Process " << mName << " performing work during time slice." << std::endl;
	}

	bool operator==(const Process &rhs)
	{
		return mName == rhs.mName;
	}

private:
	std::string mName;
};

class Scheduler final
{
public:
	Scheduler(const std::vector<Process> &processes);

	void scheduleTimeSlice();

	void removeProcess(const Process &process);

private:
	RoundRobin<Process> mProcesses;
};

Scheduler::Scheduler(const std::vector<Process> &processes)
{
	for (auto &process : processes)
		mProcesses.add(process);
}

void Scheduler::scheduleTimeSlice()
{
	try
	{
		mProcesses.getNext().doWorkDuringTimeSlice();
	}
	catch (const std::out_of_range&)
	{
		std::cerr << "No more processes to schedule." << std::endl;
	}
}

void Scheduler::removeProcess(const Process &process)
{
	mProcesses.remove(process);
}


int main()
{
	std::vector<Process> processes = { Process("1"), Process("2"), Process("3") };

	Scheduler scheduler(processes);
	for (int i = 0; i < 4; ++i)
	{
		scheduler.scheduleTimeSlice();
	}

	scheduler.removeProcess(processes[1]);
	std::cout << "Removed second process" << std::endl;

	for (int i = 0; i < 4; ++i)
	{
		scheduler.scheduleTimeSlice();
	}

	return 0;
}