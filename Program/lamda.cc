#include<stdio.h>
#include<iostream>
#include <algorithm>
#include<vector>
#include<cstring>
using namespace std;
auto find_max_element(int *p, int size) {
	vector<int> a(size);
	memcpy(&a[0],p,size);
	for(auto i:*p)
		cout<<i<<endl;
	//std::vector<int>::iterator maxEle=std::max_element(a.begin(),a.end(),[](int a,int b){return a<b});
	//int max=std::distance(a.begin(),maxEle);
	//cout<<max;
}
int main()
{
	int a[]={10,5,12,7,6,0};
	find_max_element(a,6);

}
