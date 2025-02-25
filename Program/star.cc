#include <iostream>
#include<vector>
using namespace std;
void print_columns(vector<int> heights){
    //WRITE YOUR CODE MAINLY HERE
    vector<int> v=heights;
    for(int i=0;v.size();i++)
    {
	    cout<<"size="<<v.size();
        for(int j=0;j<v[i];j++)
        {
            cout<<"*"<<"\n";
            cout<<"\t";
        }
        cout<<"\t";
    }
    cout<<"_______________";
}

int main(){
	vector<int> v={1,4,0,3,2};
    print_columns(v);
}
