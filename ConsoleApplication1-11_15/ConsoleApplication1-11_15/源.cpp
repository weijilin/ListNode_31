#define _CRT_SECURE_NO_WARNINGS 1
#if 0
class Base
{
public:
	Base(int b)
		: _b(b)
	{}

	Base(const Base& b)
		: _b(b._b)
	{}

	Base& operator=(const Base& b)
	{
		if (this != &b)
		{
			_b = b._b;
		}

		return *this;
	}

	void SetBase(int b)
	{
		_b = b;
	}

	void TestFunc(int)
	{}

	void PrintBase()
	{
		cout << _b << endl;
	}

	~Base()
	{
		cout << "Base::~Base()" << endl;
	}

	int _b;
};


// 如果基类具有无参的构造函数时，派生类必须显式定义自己的构造函数
// 并且必须在其初始化列表的位置显式调用基类的构造函数完成派生类对象
// 中基类部分成员的初始化
struct Derived : public Base
{
public:
	Derived(int b, int d)
		: Base(b)
		, _d(d)
	{}

	// 编译器给派生类生成的默认构造函数
	//Derived()
	//	: Base()
	//{}

	// 如果基类没有显式定义自己的拷贝构造函数，派生类是否定义都可以
	// 如果基类显式定义自己的拷贝构造函数，派生类必须显式定义拷贝构造函数
	// 并且需要在其拷贝构造初始化列表的位置显式调用基类的拷贝构造函数
	Derived(const Derived& d)
		: Base(d)
		, _d(d._d)
	{}

	/*
	没有涉及到资源管理时：如果派生类没有显式定义自己的赋值运算符重载，编译器会生成一份默认的，
	该默认的赋值运算符重载可以完整的赋值

	如果类中涉及到资源管理：派生类需要将自己的拷贝构造函数显式给出，必须在其内部显式调用基类的
	赋值运算符重载完成基类部分的赋值，在完成自己特有成员的赋值
	*/
	Derived& operator=(const Derived& d)
	{
		if (this != &d)
		{
			Base::operator=(d);
			_d = d._d;
		}

		return *this;
	}

	void SetDerived(int b, int d)
	{
		_b = b;
		_d = d;
	}

	void TestFunc()
	{}

	// 派生类对象：基类部分 + 派生类特有
	~Derived()
	{
		// 派生类清理自己的资源
		cout << "Derived::~Derived()" << endl;

		// 编译器在拍摄类最后一条语句之后插入一条调用基类析构函数的汇编语句
		// 清理派生类对象中属于基类部分的资源
		// call Base::~Base();
	}

	char _d;
};

void TestDerived()
{
	Derived d1(10, 20);
	Derived d2(30, 40);

	d1 = d2;
}

int main()
{
	TestDerived();
	return 0;
}
#endif

#if 0
class Base
{
public:
	Base(int b)
		: _b(b)
	{
		cout << "Base::Base()" << endl;
	}

	~Base()
	{
		cout << "Base::~Base()" << endl;
	}

	int _b;
};

struct Derived : public Base
{
public:
	Derived(int b, int d)
		: Base(b)
		, _d(d)
	{
		cout << "Derived::Derived()" << endl;
	}

	// 派生类对象：基类部分 + 派生类特有
	~Derived()
	{
		// 派生类清理自己的资源
		cout << "Derived::~Derived()" << endl;

		// 编译器在拍摄类最后一条语句之后插入一条调用基类析构函数的汇编语句
		// 清理派生类对象中属于基类部分的资源
		// call Base::~Base();
	}

	char _d;
};

// 
/*
1. 打印结果
Base::Base()
Derived::Derived()
Derived::~Derived()
Base::~Base()
*/
// 2. 函数调用次序
/*
基类构造
派生类构造
派生类析构
基类析构

创建那个类的对象，调用那个类的构造函数
析构那个类的对象，调用那个类的析构函数

Derived  d(10, 20);
调用派生类的构造函数
: 调用基类的构造函数
{}

调用派生类的析构函数
{
// 析构派生类自己的资源
// call 基类的析构函数
}
*/

void TestDerived()
{
	Derived d(10, 20);
}

int main()
{
	TestDerived();
	return 0;
}
#endif

#if 0
// C++98
// 要求：A类不能被继承
class A
{
public:
	static A GetA(int a)
	{
		return A(a);
	}

private:
	A(int a = 10)
		: _a(a)
	{}

protected:
	int _a;
};

class B : public A
{
public:
	//B()
	//	: A(10)
	//{}
};


int main()
{
	//B b;

	A a = A::GetA(10);
	return 0;
}
#endif


// C++11 final作用：修饰类时，表明该类不能被继承
class A final
{
public:
	A(int a = 10)
		: _a(a)
	{}

protected:
	int _a;
};

class B : public A
{};

int main()
{
	A a;
	return 0;
}

