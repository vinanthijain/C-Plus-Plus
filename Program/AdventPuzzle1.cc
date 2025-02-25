#include<iostream>
#include<stdio.h>
#include<fstream>
using namespace std;
int main()
{
    fstream f;
    try{
        f.open("input.txt");
        string s;
        std::string::const_iterator it ;
        int result=0;
        float num=0;
            while(1)
            {
                f>>s;
                it=s.begin();
                int i=2;
                while(s>>num !=0 && i>0) 
                {
                    result+=num;
                    i--;
                }
                if(f.eof())
                   break;
            }
            f.close();
    }   
    catch(...)
    {
        cout<<"Exception Occurred!";
    }      
}