#include<stdio.h>
#include<iostream>
#include<thread>
#include<atomic>
using namespace std;

atomic<int> counter(0);
void testAtomic()
{
	counter.fetch_add(1);
}
int main()
{
	thread t1(testAtomic);
	thread t2(testAtomic);
	t1.join();
	t2.join();
	cout<<"Counter="<<counter.load()<<endl;
}
