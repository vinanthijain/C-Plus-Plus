#include<iostream>
#include<stdio.h>
using namespace std;
int solve(int p) {
    int n=p;
    int i,j =n;
    while(n>0)
    {
	    cout<<"Executing for "<<n<<endl;
        if((n%10) %2 != 0)
        {
            n=n/10;
            continue;
        }
        else
        {
            if(i>0)
            {
		cout<<"Calling i="<<i<<endl;
                solve(i++);
            }
            if(j>0)
            {
		cout<<"Calling j="<<j<<endl;
                solve(--j);
            }
        }
    }
     return p;
}
int main()
{
	int n;
	cout<<"Enter n"<<endl;
	cin>>n;
	solve(n);
}
