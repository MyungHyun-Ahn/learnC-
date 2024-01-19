#include <iostream>


class Car
{
public:
	Car() = default;
	Car(int x, int y) : mX(x), mY(y) {}
	Car(Car &car)
	{
		this->mX = car.mX;
		this->mY = car.mY;
	}
	~Car() { std::cout << "Car is gone" << '\n'; }

	std::shared_ptr<Car> getCar()
	{
		return std::shared_ptr<Car>(this);
	}

private:
	int mX;
	int mY;
};

int main()
{
	std::shared_ptr<Car> car1 = std::make_shared<Car>(1, 2);

	std::cout << car1.use_count() << '\n';

	std::shared_ptr<Car> car2 = car1->getCar();

	std::cout << car1.use_count() << '\n';
	std::cout << car2.use_count() << '\n';
}