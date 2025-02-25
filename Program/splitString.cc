#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string>
#include <vector>
#include <sstream>
using namespace std;
int main()
{
	 string str="3 12345678912345 a 334.23 14049.30493";
	stringstream s(str);
    while(s>>str)
        cout<<str<<endl;
}
