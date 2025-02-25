#include <iostream>
#include <vector>
#include <algorithm>
#include<set>
using namespace std;
int main()
{
    vector<string> v = {{"arb"},
	    {"bul"}, 
	    {"hrv"},
	    {"ces"},
	    {"dan"},
	    {"nld"},
	    {"eng"},
	    {"fin"},
	    {"fra"},
	    {"deu"},
	    {"heb"},
	    {"hun"},
	    {"ita"},
	    {"kor"},
	    {"nor"}, 
	    {"pol"},
	    {"por"},
	    {"rus"},
	    {"srp"},
	    {"cmn"},
	    {"slk"},
	    {"spa"},
	    {"swe"},
	    {"ukr"},
	    {"cmn"},
	    {"ron"},
	    {"ell"},
	    {"slv"}};
	//vector<string> v={{"man"},{"dog"},{"cat"},{"dog"}};
  
    // Declaring a vector to store the copied value
    vector<string> v1(30);
  
  
    // Now v1 contains {10 30 100 10 30 70 80 0 0 0}
  
    vector<string>::iterator ip;
    cout << "Before: \t"<<v.size();
    for (ip = v.begin(); ip != v.end(); ++ip) 
    {
        cout << *ip << " ";
    }

    /*ip=std::unique_copy(v.begin(), v.end(),v1.begin());
     v1.resize(std::distance(v1.begin(), ip));
  
    cout << "\nAfter: \t"<<v1.size();
    for (ip = v1.begin(); ip != v1.end(); ++ip) 
    {
        cout << *ip << " ";
    }*/
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
  
    vector<string>::iterator ip1;
    cout << "\nAfter Sort:\t"<< v.size();
    set<string> s1;
    for (ip1 = v.begin(); ip1 != v.end(); ++ip1) 
    {
        cout << *ip1 << " ";
	s1.insert(*ip1);
    }
    cout << "\nAfter Sort using set:\t"<< s1.size();
    for (auto ip2 = s1.begin(); ip2 != s1.end(); ++ip2) 
    {
        cout << *ip2 << " ";
    }

    return 0;
}
