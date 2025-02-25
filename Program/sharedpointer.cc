#include<stdio.h>
#include<iostream>
#include<memory>
using namespace std;
std::shared_ptr<std::string> returnfunc()
{
	auto device=std::make_shared<std::string>("Hello");
	cout<<"Returning from func"<<*device<<endl;
	return device;
}
int main()
{
	cout<<"Returning from func"<<*returnfunc();
}
