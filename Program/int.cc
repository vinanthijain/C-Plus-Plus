#include<stdio.h>
#include<iostream>
#include <typeinfo>
using namespace std;
class A
{

};
class B{};
int main()
{
	A a;
	B b;
	if(typeid(a)==typeid(b))
	{
		cout<<"Same"<<endl;
	}

}
