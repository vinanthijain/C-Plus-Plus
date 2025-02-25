#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;
int main()
{
	bool notOne = false;
	bool isConsecutive = false;
	bool result = false;

	vector<int> v={1, 1, 1, 1, 2, 3};
	for(int v1:v)
	{
		if(v1 == 1)
		{
			cout<<"Concecutive "<<v1<<endl;
			isConsecutive = true;
		}
		if(isConsecutive == true && v1!=1)
		{
			cout<<"Not one "<<v1<<endl;
			notOne = true;
		}
		if(isConsecutive == 1 && v1 == 1 && notOne == true)
		{
			cout<<"Not Cons "<<v1<<endl;
			isConsecutive = false;
		}
	}
	cout<<"isConsecutive is "<<isConsecutive<<endl;
	if(isConsecutive == true)
	{
		cout<<"True"<<endl;
	}
	else
	{
		cout<<"False"<<endl;
	}
}
