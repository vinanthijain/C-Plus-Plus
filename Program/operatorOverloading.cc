#include <functional>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
using namespace std; 
std::function<bool (int a,int b)> myCompare = [](int a,int b)->bool const {
  std::stringstream as,bs;
  as << a;
  bs << b;
  cout<<"myCompare Called"<<endl;
  return as.str() < bs.str();
};
 
std::set<int, decltype(myCompare)> mySet(
  {0,1,3,8,377,13,21,34,2,1,233,144},
  myCompare
);
 
template<typename N,typename CMP>
std::ostream & operator<<(std::ostream & os,const std::set<N,CMP> & s) {
  for(const auto & n : s) {
	  cout<<"OO Called"<<endl;
    os << n << std::endl;
  }
  return os;
}
 
int main(int argc,char **argv) {
  std::cout << mySet << std::endl;
  return 0;
}
