#include<iostream>
#include<stdio.h>
using namespace std;
class A
{
	string str;
};
int main()
{


	A a;
    auto b = [](int a){cout <<a<<endl;};
    b(10);
}
