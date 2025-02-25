** Polymorphism:
Polymorphism is a core concept in (OOP) that allows objects of different classes to be treated as objects of a common base class. It enables a single interface to be used for different data types, and the actual method that gets called is determined at runtime based on the object type.
    There are two main types of polymorphism in C++:
    Compile-Time Polymorphism (Static Polymorphism): Compile-time polymorphism is achieved through function overloading and operator overloading.
    Run-Time Polymorphism (Dynamic Polymorphism): Run-time polymorphism is achieved through inheritance and virtual functions. It allows a base class reference or pointer to call methods of derived class objects.

** Multiple Inheritence
    Multiple inheritance is a feature of some object-oriented programming languages, including C++, that allows a class to inherit from more than one base class. This means that a derived class can inherit attributes and methods from multiple parent classes.

** The Diamond Problem
The diamond problem occurs when two base classes inherit from the same base class, and then a derived class inherits from both of these classes. This can create ambiguity about which base class's member functions and attributes to use.

#include<iostream>
using namespace std;
class Person {
// Data members of person
public:
	Person(int x) { cout << "Person::Person(int ) called" << endl; }
};

class Faculty : public Person {
// data members of Faculty
public:
	Faculty(int x):Person(x) {
	cout<<"Faculty::Faculty(int ) called"<< endl;
	}
};

class Student : public Person {
// data members of Student
public:
	Student(int x):Person(x) {
		cout<<"Student::Student(int ) called"<< endl;
	}
};

class TA : public Faculty, public Student {
public:
	TA(int x):Student(x), Faculty(x) {
		cout<<"TA::TA(int ) called"<< endl;
	}
};

int main() {
	TA ta1(30);
}
In the above program, constructor of ‘Person’ is called two times. Destructor of ‘Person’ will also be called two times when object ‘ta1’ is destructed. So object ‘ta1’ has two copies of all members of ‘Person’, this causes ambiguities. The solution to this problem is ‘virtual’ keyword. We make the classes ‘Faculty’ and ‘Student’ as virtual base classes to avoid two copies of ‘Person’ in ‘TA’ class.

** override" and "final":
override ensures that an overriding virtual function declared in a derived class has the same signature as that of the base class. final blocks further derivation of a class and further overriding of a virtual function.
Override function helps to check if 
a.There is a method with the same name in the parent class.
b.The method in the parent class is declared as “virtual” which means it was intended to be rewritten.
c.The method in the parent class has the same signature as the method in the subclass.


