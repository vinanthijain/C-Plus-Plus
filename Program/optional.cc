#include<iostream>
#include<stdio.h>
#include<optional>
using namespace std;

int main()
{
	std::optional<int16_t> opt;
	double i=27;
	opt=27;
	cout<<opt.value()<<endl;
}

