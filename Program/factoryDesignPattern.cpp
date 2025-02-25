#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
enum Type
{
	TWO,
	THREE,
	FOUR
};
class V
{
	public:
	static V* createVehicle(Type);
	virtual void display()=0;
	
};
class TWOW:public V
{
	public:
		void display()
		{
			cout<<"Hey!!! I am TWO"<<endl;
		}
};
class THREEW:public V
{
	public:
		void display()
		{
			cout<<"Hey!!! I am THREE"<<endl;
		}
};
class FOURW:public V
{
	public:
		void display()
		{
			cout<<"Hey!!! I am FOUR"<<endl;
		}
};
V* V::createVehicle(Type type)
{
	if(type == TWO)
		return new TWOW();
	else if(type == THREE)
		return new THREEW();
	else if(type == FOUR)
		return new FOURW();
	else
		return NULL;
};
class Client
{
	V *pVehicle;
	public:
	Client()
	{
		Type t= THREE;
		pVehicle=V::createVehicle(t);
	}
	~Client()
	{
		if(pVehicle)
			delete[] pVehicle;
		pVehicle = NULL;
	}
	V* getVehicle()
	{
		return pVehicle;
	}
};
int main()
{
	Client *c=new Client();
	V *v=c->getVehicle();
	v->display();	
	return 0;
}

