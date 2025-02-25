#include<iostream>
#include</home/vijain/Project/sysroots/aarch64-mbient-linux/usr/include/boost/algorithm/string.hpp>

using namespace std;
using namespace boost::algorithm;

int main()
{
  string s1,s2,s3,s4;
  s1 = "welcome to boost";
  s2 = "ITS WRITTEN IN C++";
  s3 = "#@ It'S QuItE iNtErEsTiNg **";
  s4 = "AND ITS QUITE FUN TOO!!";
   
  //converting the strings to lower case in-place
  to_lower(s1); 
  to_lower(s2);
  to_lower(s3);

  //returning the modified string to newString
  string newString = to_lower_copy(s4);

  cout<<s1<<endl;
  cout<<s2<<endl;
  cout<<s3<<endl;
  cout<<"Original string :"<<s4<<endl;
  cout<<"Modified string :"<<newString<<endl;
  
}
