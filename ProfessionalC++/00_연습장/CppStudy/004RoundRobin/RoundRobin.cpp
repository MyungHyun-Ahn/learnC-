#include <iostream>
#include <vector>
#include <string_view>

template<typename T>
class RoundRobin
{
public:
	// ȿ���� ���� ������ ���� ������ Ŭ���̾�Ʈ�κ��� �޴´�.
	RoundRobin(size_t numExpected = 0);
	virtual ~RoundRobin() = default;

	RoundRobin(const RoundRobin &src) = delete;
	RoundRobin &operator=(RoundRobin &rhs) = delete;


	// ����Ʈ�� ���� ���Ҹ� �߰��Ѵ�.
	void add(const T &element);

	// operator== �����ڸ� ȣ���� ���
	// �Ȱ��ٰ� �Ǵܵ� ù ��° ���Ҹ� �����Ѵ�.
	// getNext() ���̿� ȣ��� �� �ִ�.
	void remove(const T &element);

	// ����Ʈ�� ������ ���Ҹ� �����Ѵ�.
	// ù ��° ���Һ��� �����ؼ� ������ ���ҿ� �ٴٸ��� �ٽ� ù ��° ���ҷ� ���ƿ´�.
	// �̶� �߰��� �߰��ǰų� ������ ���ҵ� �ݿ��Ѵ�.
	T &getNext();

private:
	std::vector<T> mElements;
	// �ϳ� �̻��� ���ø� �Ű������� ������ Ÿ�Կ� ������ ���� �׻� typename Ű���带 �����ؾ� �Ѵ�.
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
	// ���Ҹ� �������� �߰��ϴ��� push_back()�� ȣ���� �����
	// vector�� ���Ҵ�ż� �ݺ��ڰ� ��ȿȭ�� �� �ִ�.
	// ������ �����Ϸ��� �ݺ����� ���� �׼��� ����� �ִ��� Ȱ���Ѵ�.
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
			// �ݺ��ڰ� �����ϴ� ���Ұ� ������ ����� ���� ���Ҹ� ����Ű�� ���� �� ���Ҹ� �����ϸ� �ݺ��ڰ� ��ȿȭ �ȴ�.
			// ������ �� ���� ������ ��ġ�� �����Ϸ��� �ݺ����� ���� �׼��� ����� Ȱ���Ѵ�.
			int newPos;

			if (mCurrentElement == end(mElements) - 1 && mCurrentElement == it)
			{
				// �ݺ��ڰ� ����Ʈ�� ������ ���Ҹ� ����Ű�� ���¿���
				// �� ���Ҹ� �����Ϸ� �ϹǷ� �ٽ� ù ��° ������ ��ġ�� �̵���Ų��.
				newPos = 0;
			}
			else if (mCurrentElement <= it)
			{
				// �׷��� �ʰ� mCurrentElement�� �����Ϸ��� ���ҳ�
				// �� ���� ���Ҹ� ����Ű�� �ִٸ� ��ġ�� ������ �ʴ´�.
				newPos = mCurrentElement - begin(mElements);
			}
			else
			{
				// �� ��� ��� �ش���� �ʴ´ٸ�
				// �� ĭ ���� �� ��ġ�� �ȴ�.
				newPos = mCurrentElement - begin(mElements) - 1;
			}

			// ���Ҹ� �����Ѵ�. (���� ���� ����)
			mElements.erase(it);

			// �ݺ��ڰ� ��ȿ�� ���¸� �����ϵ��� �����Ѵ�.
			mCurrentElement = begin(mElements) + newPos;

			return;
		}
	}
}

template<typename T>
T &RoundRobin<T>::getNext()
{
	// ���� ���� ���Ұ� ����ִ��� ���� Ȯ���Ѵ�.
	if (mElements.empty())
		throw std::out_of_range("No elements in the list");

	auto &toReturn = *mCurrentElement;

	// �ݺ��ڸ� ���� ���� ���� ���� ������ �̿��Ͽ� ������Ų��.
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