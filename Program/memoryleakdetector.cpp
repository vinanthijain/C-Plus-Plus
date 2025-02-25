#include<iostream>
#include<stdio.h>
#include<unordered_map>
using namespace std;

struct Memory{
    size_t size;
};
unordered_map<void*,Memory> mapu;
void* malloc_custom(size_t size){
    cout<<"Malloc is being called"<<endl;
    void* ptr=malloc(size);
    mapu[ptr]={size};
    return ptr;
}
void free_custom(void* ptr){
    cout<<"Free is getting called"<<endl;
    auto it=mapu.find(ptr);
    if(it!=mapu.end())
        free(ptr);
    mapu.erase(it);
}
void validate(){
    if(mapu.size()>0)
        cout<<"MemoryLeak Detected"<<endl;
}
#define malloc malloc_custom;
#define free free_custom;
int main()
{
    void* ptr=malloc_custom(10);
    free_custom(ptr);
}