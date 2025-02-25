#include<iostream>
#include<stdio.h>
using namespace std;
void fun()
{
	static int a=0;
	a++;
	cout<<a<<endl;
}
int main()
{
	for(int i=0;i<10;i++)
		fun();
}
