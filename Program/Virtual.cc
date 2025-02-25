#include<stdio.h>
#include<iostream>
using namespace std;
class Base {
	public:
	Base()
	{
		cout<<"Base's constructor"<<endl;
	}
	virtual void method() {std::cout << "from Base" << std::endl;}
public:
	virtual ~Base() {method();}
	void baseMethod() {method();}
};

class A : public Base {
	public:
	A()
	{
		cout<<"A's constructor"<<endl;
	}
	void method() {std::cout << "from A" << std::endl;}
public:
	~A() {method();}
};

int main(void) {
	Base* base = new A;
	//base->baseMethod();
	delete base;
	return 0;
}
