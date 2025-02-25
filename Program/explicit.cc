#include <iostream>
using namespace std;
class Complex {
	private:
		int first,second;
	public:
		explicit Complex(int a=0,int b=0):first(a),second(b){}
		bool operator==(Complex c){
			return c.first ==first && c.second == second;
		}
};
int main()
{
	Complex c(1,2);
	if(c == 3)
		cout<<"Different"<<endl;
	else
		cout<<"Same"<<endl;
}
