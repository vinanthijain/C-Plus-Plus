#include <iostream>
#include <string>
#include<vector>
#include<algorithm>
#include<sstream>
using namespace std;

void rvs(vector<int>& nums,int n){
  for(int i=0;i<nums.size();i=i+n)
  {
    if(i+n<=nums.size()){
      reverse(nums.begin()+i,nums.begin()+i+n);
    }
  }
} 
vector<string> split(string str,char delimiter){
  vector<string> tokens;
  stringstream s(str);
  string token;
  while(getline(s,token,delimiter)){
    tokens.push_back(token);
  }
  return tokens;
}

int main() {
  string line="1,2,3,4,5;2";
    cout << line << endl;
    vector<string> input=split(line,';');
    vector<string> strNum = split(input[0],',');
    vector<int> nums;
    for(auto i:strNum){
      nums.push_back(stoi(i));
    }
    
    int k=stoi(input[1]);
    rvs(nums,k);
    
    for(int i=0;i<nums.size();i++)
    {
      if(i>0)
        cout<<",";
      cout<<nums[i];
    }
    cout<<endl;
  
}
