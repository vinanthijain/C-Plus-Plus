#include<iostream>
#include<stdio.h>
using namespace std;
struct Node{
    Node* next;
    int data;
    Node(int x):data(x),next(nullptr){}
};

class LL{
    public:
    void insert(int x,Node* head=nullptr){
        if(head==nullptr){
            head=new Node(x);
        }
        else{
            Node* current=head;
            while(current->next!=nullptr){
                current=current->next;
            }
            Node* temp=new Node(x);
            current->next=temp;
        }
    }
    void delet(Node* head){
        if(head==nullptr)
            return;
        Node* current=head;
        while(current!=nullptr){
            Node* temp=current;
            current=current->next;
            delete temp;
        }
    }
    void display(Node* head){
        if(head==nullptr)
            return;
        Node* current=head;
        while(current!=nullptr){
            cout<<current->data<<endl;
            current=current->next;
        }
        //cout<<current->data<<endl;;
    }
};
int main(){
    LL linkedlist;
    Node* head=new Node(0);
    linkedlist.insert(1,head);
    linkedlist.insert(2,head);
    linkedlist.insert(3,head);
    linkedlist.insert(4,head);
    linkedlist.insert(5,head);
    linkedlist.delet(head);
    linkedlist.display(head);
}