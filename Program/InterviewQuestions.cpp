//1. What is the size of a virtual and nonvirtual class in 64 bit machine.Ans=> 8 and 1 https://shaharmike.com/cpp/vtable-part1/
#include<iostream>
using namespace std;

class NonVirtualClass {
 public:
  void foo() {}
};

class VirtualClass {
 public:
  virtual void foo() {}
};

int main() {
  cout << "Size of NonVirtualClass: " << sizeof(NonVirtualClass) << endl;
  cout << "Size of VirtualClass: " << sizeof(VirtualClass) << endl;
}
