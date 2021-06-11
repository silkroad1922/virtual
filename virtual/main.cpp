#include <fstream>
#include <string>
#include <iostream>

using namespace std;


class Base
{

public:
	Base() : next(nullptr) {
	}
	virtual void use(const string& request)
	{
		int a = stoi(request);
		int sum = 0;
		while (a>0)
		{
			sum += a % 10;
			a /= 10;
		}
		this->next->use(to_string(sum));
	}
	Base* SetNext(Base* other)
	{
		this->next = other;
		return other;
	}
	virtual ~Base() 
	{
		std::cout << "Destructor Base" << std::endl;
		delete next;
	}
protected:
	Base* next;
};

class A : public Base
{
public:
	void use(const string&request) override
	{
		int a = stoi(request);
		a *= a;
		this->next->use(to_string(a));
	}
	~A()
	{
		std::cout << "Destructor A" << std::endl;
	}
};
class B : public Base
{
private:
	fstream file;
public:

	B() : file("result.txt", std::fstream::in | std::fstream::out | std::fstream::app)
	{

	}
	void use(const string& request) override
	{
		file << request;
		file << '\n';

	}
	~B()
	{
		std::cout << "Destructor B" << std::endl;
	}
};


void ClientCode(string path, Base& obj)
{
	fstream file;
	string msg;
	file.open(path, ios::in);
	if (!file.is_open())
	{
		cout << "fail" << endl;
	}
	while (getline(file,msg,','))
	{
		obj.use(msg);
	}

}

int mult(int a, int b)
{
	return a * b;
}
int main()
{


	Base* base = new Base;

	base->SetNext(new A)->SetNext(new B);

	ClientCode("test.txt",*base);

	delete base;


	return 0;
}