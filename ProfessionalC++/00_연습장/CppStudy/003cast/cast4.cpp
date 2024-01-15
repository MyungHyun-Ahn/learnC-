#include <iostream>


class Parent
{
public:
	Parent() = default;
	Parent(int x_, int y_) : x(x_), y(y_) {}
	virtual ~Parent() { }

protected:
	int x, y;
};

class Child : public Parent
{
public:
	Child() = delete;
	Child(int x_, int y_, int z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}
	
	virtual ~Child() {}

private:
	int z;
};

class NoneClass
{
public:
	NoneClass() = default;
	NoneClass(int x_) : x(x_) {}
	~NoneClass() = default;

private:
	int x;
};

int main()
{
	int x = 10;
	int *ptr = &x;

	unsigned int *ptr1 = reinterpret_cast<unsigned int *>(ptr); // ������ ����
	short *ptr2 = reinterpret_cast<short *>(ptr); // ������ ����


	Child *ch = new Child(1, 2, 3);
	Parent *pa1 = reinterpret_cast<Parent *>(ch);
	Parent *pa2 = dynamic_cast<Parent *>(ch);
	Parent *pa3 = static_cast<Parent *>(ch);

	Parent *pa = new Parent(1, 2);
	Child *ch1 = reinterpret_cast<Child *>(pa); // �׳� ĳ���õ�
	Child *ch2 = dynamic_cast<Child *>(pa); // RTTI�� �߸��� �� �ľ��ϰ� nullptr
	Child *ch3 = static_cast<Child *>(pa); // �׳� ĳ���õ�

	NoneClass *nc = new NoneClass(1);
	Child *nch1 = static_cast<Child *>(nc); // ������ ����
	Child *nch2 = reinterpret_cast<Child *>(nc); // �׳� ĳ���õ�

	delete ch;
	delete pa;

	return 0;
}