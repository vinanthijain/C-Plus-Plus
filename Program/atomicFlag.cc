#include<iostream>
#include<stdio.h>
#include<thread>
#include<atomic>
using namespace std;
atomic_flag flag=ATOMIC_FLAG_INIT;
void testAtomic(int id)
{
	for(int i=0;i<5;i++)
	{
		while(flag.test_and_set(memory_order_acquire))
		{
		}
		cout<<"Thread "<<id<<" is running"<<endl;
		flag.clear(memory_order_release);
	}
}
int main()
{
	thread t1(testAtomic,1);
	thread t2(testAtomic,2);
	t1.join();
	t2.join();
}
