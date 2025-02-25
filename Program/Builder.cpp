#include<iostream>
#include<stdio.h>
using namespace std;
class Pizza{
    string dough,topping;
    public:
    void setDough(string d)
    {
        dough = d;
    }
    void setTopping(string t)
    {
        topping = t;
    }
    void display()
    {
        cout<<"Pizza is prepared";
    }
};
class Builder{
    public:
    virtual void buildDough() =0;
    virtual void buildTopping() =0;
    virtual void display() =0;
};
class MargharetaBuilder: public Builder
{
    Pizza p;
    public:
    void buildDough()
    {
        p.setDough("thin");
    }
    void buildTopping()
    {
        p.setTopping("Olives");
    }
    void display()
    {
        p.display();
    }
};
class Director
{
    Builder* build;
    public:
    Director(Builder* b):build(b){}
    void construct()
    {
        build->buildDough();
        build->buildTopping();
    }
};
int main()
{
    MargharetaBuilder* b=new MargharetaBuilder();
    Director d(b);
    d.construct();
    b->display();
}