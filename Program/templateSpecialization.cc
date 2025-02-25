#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
template<typename T> 
T add(T z, T x)
{
	return x+z;
}

//template char add(char x,char y);
template<> char* add<char*>(char *x,char *y)
{
	cout<<"Calling Char*"<<endl;
	return strcmp(x,y) > 0 ? x:y;
}
int main()
{
	char *a{"A"};
	char *b{"B"};
	cout<<"1"<<add(1,2)<<endl;
	cout<<"2"<<add(a,b)<<endl;
}
