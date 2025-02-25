#include<stdio.h>
#include<iostream>
using namespace std;
class A
{
public:
	A()
	{
		cout<<"A constructor"<<endl;
	}
	virtual ~A()
	{
		cout<<"A destructor"<<endl;
	}
  
   virtual void display()
    {
        cout << "A's display" << endl;
    }
};
class B :public A
{
public:
	B()
	{
		cout<<"B constructor"<<endl;
	}
	~B()
	{
		cout<<"B destructor"<<endl;
	}
    void display()
    {
        cout << "B's display" << endl;
    }
};
int main()
{
    A *a = new B();
    a->display();
    delete a;
}
