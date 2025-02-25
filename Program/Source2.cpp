#include<stdio.h>
#include<iostream>
using namespace std;
class A
{
public:
    void display()
    {
        cout << "A's display" << endl;
    }
};
class B :public A
{
public:
    void display()
    {
        cout << "B's display" << endl;
    }
};
int main()
{
    A a = new B();
    b->display();
}