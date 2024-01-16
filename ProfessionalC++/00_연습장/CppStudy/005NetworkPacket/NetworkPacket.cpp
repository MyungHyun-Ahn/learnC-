#include <iostream>
#include <queue>

template<typename T>
class PacketBuffer
{
public:
	// maxSize�� 0�� ��� ũ�� ������ ����.
	PacketBuffer(size_t maxSize = 0);

	virtual ~PacketBuffer() = default;

	// ���ۿ� ��Ŷ�� �����Ѵ�.
	// ���ۿ� ������ ��� ��Ŷ�� ������ ���� false�� �����ϰ�,
	// ������ ���� true�� �����Ѵ�.
	bool bufferPacket(const T &packet);

	// ������ ��Ŷ�� �����Ѵ�. ���۰� ����ٸ� out_of_range �ͼ����� ������.
	T getNextPacket();
	
private:
	std::queue<T> mPackets;
	size_t mMaxSize;
};

template<typename T>
PacketBuffer<T>::PacketBuffer(size_t maxSize) : mMaxSize(maxSize)
{
}

template<typename T>
bool PacketBuffer<T>::bufferPacket(const T &packet)
{
	if (mMaxSize > 0 && mPackets.size() == mMaxSize)
		return false;

	mPackets.push(packet);
	return true;
}

template<typename T>
T PacketBuffer<T>::getNextPacket()
{
	if (mPackets.empty())
		throw std::out_of_range("Buffer is empty");

	T temp = mPackets.front();
	mPackets.pop();

	return temp;
}


class IPPacket final
{
public:
	IPPacket(int id) : mID(id) {}
	int getID() const { return mID; }

private:
	int mID;
};


int main()
{
	PacketBuffer<IPPacket> ipPackets(3);

	for (int i = 0; i < 4; ++i)
	{
		if (!ipPackets.bufferPacket(IPPacket(i)))
			std::cout << "Packet " << i << " dropped (queue is full)." << std::endl;
	}

	while (true)
	{
		try
		{
			IPPacket packet = ipPackets.getNextPacket();
			std::cout << "Processing packet " << packet.getID() << std::endl;
		}
		catch (const std::out_of_range &)
		{
			std::cout << "Queue is empty." << std::endl;
			break;
		}
	}

	return 0;
}