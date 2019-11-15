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


// �����������޲εĹ��캯��ʱ�������������ʽ�����Լ��Ĺ��캯��
// ���ұ��������ʼ���б��λ����ʽ���û���Ĺ��캯��������������
// �л��ಿ�ֳ�Ա�ĳ�ʼ��
struct Derived : public Base
{
public:
	Derived(int b, int d)
		: Base(b)
		, _d(d)
	{}

	// �����������������ɵ�Ĭ�Ϲ��캯��
	//Derived()
	//	: Base()
	//{}

	// �������û����ʽ�����Լ��Ŀ������캯�����������Ƿ��嶼����
	// ���������ʽ�����Լ��Ŀ������캯���������������ʽ���忽�����캯��
	// ������Ҫ���俽�������ʼ���б��λ����ʽ���û���Ŀ������캯��
	Derived(const Derived& d)
		: Base(d)
		, _d(d._d)
	{}

	/*
	û���漰����Դ����ʱ�����������û����ʽ�����Լ��ĸ�ֵ��������أ�������������һ��Ĭ�ϵģ�
	��Ĭ�ϵĸ�ֵ��������ؿ��������ĸ�ֵ

	��������漰����Դ������������Ҫ���Լ��Ŀ������캯����ʽ���������������ڲ���ʽ���û����
	��ֵ�����������ɻ��ಿ�ֵĸ�ֵ��������Լ����г�Ա�ĸ�ֵ
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

	// ��������󣺻��ಿ�� + ����������
	~Derived()
	{
		// �����������Լ�����Դ
		cout << "Derived::~Derived()" << endl;

		// �����������������һ�����֮�����һ�����û������������Ļ�����
		// ������������������ڻ��ಿ�ֵ���Դ
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

	// ��������󣺻��ಿ�� + ����������
	~Derived()
	{
		// �����������Լ�����Դ
		cout << "Derived::~Derived()" << endl;

		// �����������������һ�����֮�����һ�����û������������Ļ�����
		// ������������������ڻ��ಿ�ֵ���Դ
		// call Base::~Base();
	}

	char _d;
};

// 
/*
1. ��ӡ���
Base::Base()
Derived::Derived()
Derived::~Derived()
Base::~Base()
*/
// 2. �������ô���
/*
���๹��
�����๹��
����������
��������

�����Ǹ���Ķ��󣬵����Ǹ���Ĺ��캯��
�����Ǹ���Ķ��󣬵����Ǹ������������

Derived  d(10, 20);
����������Ĺ��캯��
: ���û���Ĺ��캯��
{}

�������������������
{
// �����������Լ�����Դ
// call �������������
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
// Ҫ��A�಻�ܱ��̳�
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


// C++11 final���ã�������ʱ���������಻�ܱ��̳�
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

