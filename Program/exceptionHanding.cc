#include<iostream>
using namespace std;
int main()
{
	int miles=13;
	int gallon=0;
	double milespergallon;
	try{
		//milespergallon=static_cast<double>(miles)/gallon;
		if(gallon==0 ||miles<=0)
		{
			cout<<"Throwing"<<endl;
			throw std::string("Miles or Gallons is 0");
		}
	}
	catch(int z)
	{
		cout<<"Miles or Gallons are 0"<<endl;
	}
	catch(std::string &x)
	{
		cout<<"Exception thrown"<<x<<endl;
	}
	catch(...)
	{
		cout<<"Unknown Exception"<<endl;
	}
	
}
