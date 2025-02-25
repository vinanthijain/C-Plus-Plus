#include<iostream>
#include<thread>
#include<mutex>
#include<shared_mutex>
using namespace std;
int val=0;
shared_mutex shlock;
void reader(int id){
    shared_lock<shared_mutex> lock(shlock);
    cout<<val<<endl;
}
void writer(int id){
    unique_lock<shared_mutex> lock(shlock);
    val++;
    cout<<val<<endl;
}
int main(){
    thread readers[]={thread(reader,1),thread(reader,2)};
    thread writers[]={thread(writer,1),thread(writer,2)};

    for(auto& i:readers){
        i.join();
    }
    for(auto& i:writers){
        i.join();
    }
}