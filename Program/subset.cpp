#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include <algorithm>
#include<unordered_set>
#include <memory>
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
#include <unistd.h>
#include<semaphore.h>
using namespace std;

void Perm(vector<int> v,vector<int> current,int index,std::vector<std::vector<int>>& result)
{
    result.push_back(current);
    for(int i=index;i<v.size();i++)
    {
        current.push_back(v[i]);
        //cout<<"Pushing "<<v[i]<<endl;
        Perm(v,current,i+1,result);
        current.pop_back();
    }
}

std::vector<std::vector<int>> subset(std::vector<int> v)
{
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    Perm(v,current,0,result);
    for(auto i:result)
    {
        std::cout << "[";
        for(auto j:i)
            cout<<j;
        std::cout << "]\n";
    }
    return result;
}
int main()
{
    std::vector<int> v={1,2,3};
    std::vector<std::vector<int>> result=subset(v);
}
