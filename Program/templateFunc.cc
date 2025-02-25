#include<iostream>
#include<stdio.h>
#include "templateFunc.h"
using namespace std;

template<typename T>
void add(T val)
{
	int32_t c=65538.1234;
	uint16_t z=123.46;
	cout<<z<<endl;
}

int main()
{
	add<int>(546);
}
