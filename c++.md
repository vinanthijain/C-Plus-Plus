NOTE:
====
1)char *s = "geeksforgeeks";
s[0] = 'e';

Above program will give segmentation fault.

2)sizeof('a') will print sizeof(int) in C and sizeof(char) in C++
3)Class that contains more than 0 virtual functions will have an vtable.Each object of virtual class will have an vptr.

4)Stack is faster than Heap
5)Instead of (miles)/gallon, if we do static_cast<double>(miles)/gallon when gallon is 0, it prints inf instead of throwing an exception.
6)If an exception is thrown but not caught, C++ tries to find a handler by unwinding the stack.



Interview Questions:
----------------------------

5.What is unit,integration,smoke,regression testing
    
6.What is mocking
    Mocking in software testing refers to the practice of creating mock objects that simulate the behavior of real objects in controlled ways
8.What is smart pointers and different types of it
10.what is template 
    templates are a powerful feature that allows the creation of generic functions and classes. 
    In some cases, you might want to handle specific data types differently. Template specialization allows you to define a specific implementation for a particular type:
11.different types of casting
    static_cast is used for compile-time type conversions that are well-defined . 
    Base* b = new Derived();
    Derived* d = static_cast<Derived*>(b);
    dynamic_cast is used for polymorphic type conversions and performs a run-time check to ensure the validity of the cast. It is typically used for safe downcasting in class hierarchies
    Base* b = new Derived();
    Derived* d = dynamic_cast<Derived*>(b);
    const_cast is used to add or remove the const qualifier from a variable. It is the only cast that can be used to change the constness of an object.
    const int x = 5;
    int* p = const_cast<int*>(&x);
    reinterpret_cast is used for low-level reinterpreting of the bit patterns of an object. It can cast any pointer type to any other pointer type, even if they are unrelated.
    int i = 65;
    char* p = reinterpret_cast<char*>(&i);

13.how is exception handling done? ex: stack unwinding
    Exception handling in C++ is a mechanism that allows a program to deal with unexpected situations (errors) in a controlled manner. It uses three main keywords: try, catch, and throw.
    Stack unwinding is the process of cleaning up the stack when an exception is thrown. When an exception is thrown, the runtime system searches for a matching catch block. During this process, all local objects in the functions along the call chain are destroyed in the reverse order of their creation. This is essential to ensure that resources are properly released, and no resource leaks occur.
    When an exception is thrown during stack unwinding, it creates a critical situation because the C++ standard prohibits exceptions from escaping destructors during stack unwinding. If such a situation arises, the program is typically terminated.(std::terminate Called)
    }
16.Lambda function
    Lambda functions, also known as lambda expressions, are a concise way to create anonymous functions in C++. They are particularly useful for short snippets of code that are used only once, such as in algorithms or for custom sorting/comparison operations

    int main() {
        auto add = [](int a, int b) -> int {
            return a + b;
        };

        std::cout << "Sum: " << add(3, 4) << std::endl;
        return 0;
    }

1. What is RAII, and how it should be used?
=> Resource Acquisition Is Initialization means that an object’s creation and destruction are tied to a resource being acquired and released.
If resources are managed in an non-object oriented approach and if we forget to close the file, it will result in an increased memory consumption.
In an OO approach, if resources are managed in an function, the period between constructor of the class and function call, there will be no file to write into
Acquire the file in the `Logger` constructor itself is an proper way to access a file and that is RAII

==================================================================================================================

Volatile:
volatile keyword is used to inform the compiler that a variable's value may be changed at any time and not to optimize it.It can change outside of the control or awareness of the program itself. This is often the case in embedded systems, multi-threaded environments, or when working with hardware registers or memory-mapped I/O
======================================================================================================================
==========================================================================================================================
9.What is the importance of "constexpr" ?
The idea is to spend time in compilation and save time at run time (similar to template metaprogramming).  constexpr specifies that the value of an object or a function can be evaluated at compile-time and the expression can be used in other constant expressions.

==========================================================================================================================
10.How to avoid narrowing conversion ?
By TypeCasting
==========================================================================================================================
What are lambdas ? What are the capture modes available ?
Lambda expressions are used to write short snippet of code which are not going to be reused and which doesnot require a name. 
auto square = [](int i)
    {
        return i * i;
    };
Capture modes available are by value and by reference [=,&]
===========================================================================================================================
When to use "mutable" ?
mutable keyword allows you to modify a variable inside a const context
==========================================================================================================================
What is Rvalue reference and what do you understand by move semantics ?
The primary purpose of introducing an rvalue is to implement move semantics

In C++03, there was a costly and unnecessary deep copies that can happen implicitly when objects are passed by value. We can avoid the performance hit due to deep copy by using a rvalue reference.

A(A&& other) noexcept    // C++11 - specifying non-exception throwing functions
{
  mData =  other.mData;  // shallow copy or referential copy
  other.mData = nullptr;
}

A& operator=(A&& other) noexcept
{
  mData =  other.mData;
  other.mData = nullptr;
  return *this;
}
==========================================================================================================================
How unordered STL containers are internally implemented ?
The unordered set in C++ is implemented using a hash table.
==========================================================================================================================
What is perfect forwarding or What are variadic templates ?
Variadic Templates:
Variadic templates allow you to create functions or classes that can accept a variable number of arguments. This feature was introduced in C++11 and enables you to write generic code that works with a different number of arguments.
Here's a simple example of a variadic template function that prints any number of arguments:

// Base case to stop recursion
void printArgs() {}

// Variadic template function for printing arguments
template <typename T, typename... Args>
void printArgs(T first, Args... rest) {
    std::cout << first << " ";
    printArgs(rest...);
}

int main() {
    printArgs(1, 2, 3, "four", 5.5);
    return 0;
}
In this example, printArgs is a variadic template function that recursively prints each argument until the base case is reached.

Perfect Forwarding:
Perfect forwarding is a mechanism that allows you to forward both lvalues and rvalues (references and values) with their original value category. This is particularly useful when dealing with template functions that need to preserve the value category of the arguments.
This is achieved using universal references(T&&) and std::forward
Consider a function template that forwards its arguments to another function:
#include <iostream>
template <typename T>
void wrapper(T&& arg) {
    // Do something with arg
    std::cout << arg << std::endl;
}

template <typename T>
void forwarder(T&& arg) {
    wrapper(std::forward<T>(arg));
}

int main() {
    int x = 42;
    forwarder(x);        // Calls wrapper with lvalue
    forwarder(123);      // Calls wrapper with rvalue
    forwarder("hello");  // Calls wrapper with rvalue (for const char*)
    
    return 0;
}
In this example, forwarder forwards its argument to wrapper using std::forward, preserving the original value category (lvalue or rvalue).

When these two features are combined, you can create highly generic and flexible code that works with a variable number of arguments and maintains the correct value categories during forwarding, avoiding unnecessary copies and ensuring proper behavior for both lvalues and rvalues.
==========================================================================================================================

Which types of casts exists in C++?
1.Implicit Cast-It is done by compiler on its own and it causes overflow and signs may be lost when converting to unsigned.Data types are upgraded to data type of the variable with largest data type.
2.Explicit Cast-This process is also called type casting and it is user-defined. Here the user can typecast the result to make it of a particular data type.
3.Conversion using Cast operator
	a.Static Cast-It performs compile-time type conversion and is mainly used for explicit conversions that are considered safe by the compiler. 
	b.Dynamic Cast-The dynamic_cast operator is mainly used to perform downcasting (converting a pointer/reference of a base class to a derived class). It ensures type safety by performing a runtime check(RTTI) to verify the validity of the conversion.
			Animal* animalPtr = new Dog(); 
			Dog* dogPtr = dynamic_cast<Dog*>(animalPtr); 
	c.Const Cast-The const_cast operator is used to modify the const or volatile qualifier of a variable
			const int number = 5; 
			const int* ptr = &number; 
			int* nonConstPtr = const_cast<int*>(ptr); 
			*nonConstPtr = 10; 
	d.Reinterpret Cast-The reinterpret_cast operator is used to convert the pointer to any other type of pointer. It does not perform any check whether the pointer converted is of the same type or not.
			int number = 10;
			int* numberPointer = &number;
			char* charPointer = reinterpret_cast<char*>(numberPointer);
==========================================================================================================================
What happens if dynamic_cast fails?
>it returns nullptr when using pointers
If dynamic_cast fails when used with references, it throws a std::bad_cast exception.
==========================================================================================================================
What are C-Style cast and why should you avoid them?
Lack of Readability:

C-style casts can be less readable compared to more explicit C++ casting operators. Each type of cast serves a distinct purpose, and using a C-style cast does not convey the specific intention of the cast.
No Compile-Time Checks:
C-style casts provide minimal compile-time checking. They attempt to perform various conversions without clearly specifying which type of conversion is intended. This lack of specificity can lead to unintended and potentially unsafe conversions.
Unsafe Conversions:
C-style casts can perform unsafe conversions, such as casting away const qualifiers using const_cast, or performing unrelated type conversions using reinterpret_cast. These conversions might lead to undefined behavior.
Compiler Warnings:
Modern C++ compilers are equipped with better diagnostics and can provide warnings or errors for specific casting operations. Using C++ casting operators (static_cast, dynamic_cast, etc.) allows the compiler to perform more checks and issue warnings or errors when unsafe conversions are detected.
Semantic Clarity:
C++ casting operators have semantic clarity. When you see a static_cast or dynamic_cast, it immediately indicates the type of conversion being performed. This makes the code more maintainable and easier to understand for both the original developer and others who may read the code.
==========================================================================================================================
What does std::variant, std::string_view, std::optional is used for ?
1. std::variant:
std::variant is a C++17 feature that provides a type-safe union. It can hold a value from a fixed set of types. This is particularly useful when you want a variable to be able to store different types, but you want to ensure type safety at compile-time.

int main() {
    std::variant<int, double, std::string> myVariant;

    myVariant = 42;
    std::cout << std::get<int>(myVariant) << std::endl;

    myVariant = 3.14;
    std::cout << std::get<double>(myVariant) << std::endl;

    myVariant = "Hello, C++";
    std::cout << std::get<std::string>(myVariant) << std::endl;

    return 0;
}
This allows you to create a variable that can hold an int, double, or std::string and switch between them.

2. std::string_view:
std::string_view is a lightweight, non-owning reference to a substring of a std::string or a character array. It's useful for efficiently working with portions of strings without the need to create a separate copy.

#include <iostream>
#include <string_view>

int main() {
    std::string str = "Hello, World!";
    std::string_view view(str.data() + 7, 5);  // View "World" in the original string

    std::cout << view << std::endl;  // Outputs "World"

    return 0;
}
std::string_view is often used in function interfaces where you want to operate on parts of strings without copying the data.

3. std::optional:
std::optional is a C++17 feature that provides a way to represent an optional (nullable) value. It's useful when you have a value that might be absent and you want to avoid using sentinel values (like null pointers).

Here's a basic example:

#include <optional>
#include <iostream>

std::optional<int> divide(int a, int b) {
    if (b != 0) {
        return a / b;
    } else {
        return std::nullopt;  // Represents an absent value
    }
}

int main() {
    auto result = divide(10, 2);

    if (result) {
        std::cout << "Result: " << *result << std::endl;
    } else {
        std::cout << "Cannot divide by zero." << std::endl;
    }

    return 0;
}
std::optional is often used in scenarios where a function may not always return a valid result and allows for more expressive and safer code compared to using null pointers or sentinel values.
==========================================================================================================================

What is pimpl idiom ?
PIMPL, which stands for "Pointer to IMPLementation," is an idiom in C++ used for managing implementation details in a way that helps minimize dependencies, reduce compilation times, and improve encapsulation. The PIMPL idiom is a technique that allows you to hide the internal details of a class by using a pointer to a separately allocated implementation class (often referred to as the "impl" class).

The primary motivation behind using the PIMPL idiom is to reduce compile-time dependencies. If the implementation details of a class are included in the header file, any change to the implementation requires recompilation of all source files that include the header. By moving the implementation details to a separate class, changes to the implementation only affect the source file that defines the implementation, avoiding the need to recompile all files that include the header.

Here's a simple example to illustrate the PIMPL idiom:
// MyClass.h (public interface)

class MyClass {
public:
    MyClass();
    ~MyClass();

    void doSomething();

private:
    class Impl;  // Forward declaration of the implementation class
    Impl* pImpl;  // Pointer to the implementation class
};
// MyClass.cpp (implementation)

#include "MyClass.h"

class MyClass::Impl {
public:
    void doSomethingPrivate() {
        // Implementation details
    }
};

MyClass::MyClass() : pImpl(new Impl) {}

MyClass::~MyClass() {
    delete pImpl;
}

void MyClass::doSomething() {
    pImpl->doSomethingPrivate();
}
In this example:

The public interface (MyClass.h) contains only the necessary declarations for the public interface of MyClass.
The private implementation details are encapsulated in a separate class (MyClass::Impl) defined in the source file (MyClass.cpp).
The MyClass class holds a pointer to the implementation (Impl) using the PIMPL idiom.
Using the PIMPL idiom can provide benefits such as:

Reducing compilation times, as changes to the implementation don't affect the clients of the class.
Enhancing encapsulation by hiding implementation details.
Minimizing header file dependencies, leading to cleaner code.
However, it also introduces the overhead of dynamic memory allocation for the implementation class and requires proper memory management to avoid memory leaks. C++11 and later versions offer smart pointers (like std::unique_ptr) that can help manage the lifetime of the implementation class more safely.
==========================================================================================================================

Are you familiar with functional programming? If so, does it exist in C++? To what extend?
while C++ is primarily an object-oriented programming language, it does provide support for functional programming features. Functional programming is a programming paradigm that treats computation as the evaluation of mathematical functions and avoids changing state and mutable data. Key features of functional programming include immutability, first-class functions, and higher-order functions.

Here are some functional programming features and concepts that exist in C++:

First-Class Functions:

C++ supports first-class functions, meaning functions can be treated as first-class citizens. They can be assigned to variables, passed as arguments to other functions, and returned as values from functions.
#include <iostream>
#include <functional>

int add(int a, int b) {
    return a + b;
}

int main() {
    // Function pointer
    int (*funcPtr)(int, int) = add;

    // Using std::function
    std::function<int(int, int)> func = add;

    std::cout << func(2, 3) << std::endl;  // Output: 5

    return 0;
}
Lambda Expressions:

C++11 introduced lambda expressions, which allow you to define anonymous functions in a concise and expressive way.
#include <iostream>

int main() {
    // Lambda expression
    auto add = [](int a, int b) { return a + b; };

    std::cout << add(2, 3) << std::endl;  // Output: 5

    return 0;
}
Higher-Order Functions:

C++ supports higher-order functions, which are functions that take other functions as parameters or return functions as results.
#include <iostream>
#include <functional>

template <typename T>
T twice(const std::function<T(T)>& f, T x) {
    return f(f(x));
}

int main() {
    auto square = [](int x) { return x * x; };
    std::cout << twice(square, 2) << std::endl;  // Output: 16
    return 0;
}
Immutability:

While C++ is not inherently immutable, you can achieve immutability by using const and avoiding mutable data structures.
#include <iostream>

int main() {
    const int x = 42;  // Immutable variable
    // x = 10;  // Error: Cannot modify an immutable variable
    return 0;
}
Functional Algorithms:

The C++ Standard Template Library (STL) provides functional algorithms like std::transform, std::accumulate, and others, which allow you to apply functions to ranges of elements.

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Functional algorithm: std::transform
    std::transform(numbers.begin(), numbers.end(), numbers.begin(), [](int x) { return x * 2; });

    // Functional algorithm: std::accumulate
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);

    std::cout << sum << std::endl;  // Output: 30

    return 0;
}
While C++ supports several functional programming features, it's important to note that C++ is a multi-paradigm language, and developers often use a combination of object-oriented, procedural, and functional programming techniques based on the requirements of their projects.
==========================================================================================================================
Have you heard of Rule of Zero(Three/Five/Six) in C++? What it means? What rule do you prefer?
=>
==========================================================================================================================
https://www.fluentcpp.com/2019/04/23/the-rule-of-zero-zero-constructor-zero-calorie/

Q: Can you roughly categorize different classes of IPC frameworks? eg. Sockets vs Message Queue or ZeroMQ vs DBus?
A:roughly 2 types: broker vs direct
brokers usually offer more convenience: API (just gotta get it to the broker), message buffering (peer's offline) but scaling them is harder
direct communication offers less convenience but better performance: no broker hop + bottleneck
protocol topic is a separate issue, ie what data to send


Q: What is an RPC? Can it be asynchronous?
A:  Usually no. The classic RPC is a blocking request/response call. However, async APIs usually use an initial RPC to initiate the action that is later acknowledged.

Q: To what extend can you test IPC code in C++? What design patterns might help you test more IPC code on a unit test level?
A:can be tested but needs clear interfaces for the net/IPC code so you can mock at the lowest level
usually not done since in the C++ ecosystem net/IPC libs often come without interface definitions
other forms of dependency injection/meta polymorphism also possible, eg link against mock lib

Q: What challenges do you see when testing a service with an asynchronous API outside of C++?
A: 'system' becomes sum of async interactions
mocks used in the tests might not reflect async nature of mocked service
testing relies on technical requirements/response times (SLAs)

Template Specialization:
===============
template<typename T>
T add(T z, T x)
{
}

Above code ie, Templates will not work for Chars and Strings.
Template specialization allows you to provide a specific implementation for a particular set of template arguments. It allows you to tailor your generic template for specific types or conditions.
template<> 
char* add<char*>(char *x,char *y)

Template Parameter Pack: It can accept any number and any type of parameters.
template<typename... Params>


Explicit Constructors
===============
Explicit Keyword in C++ is used to mark constructors to not implicitly convert types in C++.
if a class has a constructor which can be called with a single argument, then this constructor becomes a conversion constructor because such a constructor allows conversion of the single argument to the class being constructed. In this case, when com1 == 3.0 is called, 3.0 is implicitly converted to Complex type because the default constructor can be called with only 1 argument because both parameters are default arguments and we can choose not to provide them.
We can avoid such implicit conversions as these may lead to unexpected results

#include <iostream>
using namespace std;
class Complex {
        private:
                int first,second;
        public:
                Complex(int a=0,int b=0):first(a),second(b){}
                bool operator==(Complex c){
                        return c.first ==first && c.second == second;
                }
};
int main()
{
        Complex c(1,2);
        if(c == 3)
                cout<<"Different"<<endl;
        else
                cout<<"Same"<<endl;
}

https://learn.microsoft.com/ru-ru/cpp/cpp/welcome-back-to-cpp-modern-cpp?view=msvc-170
https://www.cppstories.com/2018/06/variant/
https://www.educative.io/blog/modern-multithreading-and-concurrency-in-cpp
https://www.cppstories.com/2022/20-smaller-cpp20-features/
https://luxoft.workplace.com/work/knowledge/1742792106160053

ToDo:
declType

Mbition:
======
what are virtual destructors?
    When you delete an object through a pointer to a base class, the base class's destructor is called by default if the destructor is not virtual. This can lead to resource leaks because the destructors of derived classes are not called. 

shared pointers are allocated memory from stack or heap?->Heap

difference between stack and heap?
    Aspect              Stack                                           Heap
    Definition          Memory for local variables and function calls   Memory for dynamic allocation
    Allocation          Automatic (by compiler)                         Manual (by programmer)
    Deallocation        Automatic (scope-bound)                         Manual (by programmer)
    Lifetime            Scoped                                          Flexible
    Access Time         Fast                                            Slower
    Size Limitations    Limited                                         Larger
    Usage               Local variables, function calls                 Dynamic data, objects
    Fragmentation       None                                            Possible

what happens if i access uninitialized memory in c++
    Accessing uninitialized memory in C++ can lead to undefined behavior, which means that the behavior of the program can be unpredictable and can vary from run to run, platform to platform, or even compiler to compiler

which tool will be used to identify memory leaks? ->Valgrind(valgrind --leak-check=full ./executable)

can we pass const reference to unique pointer - NO  because std::unique_ptr is designed to have exclusive ownership of the object it manages, and allowing a const reference to a std::unique_ptr would break the unique ownership semantics

can we pass const reference to shared pointer - In this case, the reference count isn't incremented, and the callee can access the pointer as long as the caller doesn't go out of scope.
where do we use weak pointers
    std::weak_ptr is used to address specific scenarios where you need to reference an object managed by a std::shared_ptr without affecting its reference count. This can prevent certain problems, such as cyclic dependencies, that can occur when using std::shared_ptr alone

Write a program to find the minimum number in an unsorted array

Luxoft:
=====
What inheritance specifiers allow dynamic cast? - Public because The authors of a class don't want outside users to access protected/private parent classes
delete p vs delete[] p
    delete p and delete[] p are used to deallocate memory that was previously allocated with new and new[], respectively
    Used to deallocate memory that was allocated for a single object using new.
    Used to deallocate memory that was allocated for an array of objects using new[]
free/malloc vs new/delete
    Use malloc/free when working with raw memory or interfacing with C libraries where object construction and destruction are not necessary.
    Use new/delete in C++ for object-oriented programming, where constructors and destructors handle initialization and cleanup.
Memory alignment (padding, alignof, alignas)
    Padding is extra space added between data members of a structure or class to ensure that each member is correctly aligned according to its alignment requirement. This can result in wasted space but ensures that data members are accessed efficiently.
    The alignof operator in C++ returns the alignment requirement of a type. This can be useful to determine the required alignment of a type at compile-time.
    The alignas specifier allows you to specify the alignment requirement for a variable or a type. This can be used to ensure that variables are aligned to a specific boundary.
Initialization time of static variables

SIGSEGV and memory protection
    SIGSEGV: Indicates an attempt to access unauthorized memory, commonly due to dereferencing invalid pointers, buffer overflows, etc.
    Memory Protection: Enforced by the operating system to control access to memory regions, ensuring system stability and security.
    Virtual Memory: Abstracts physical memory, providing isolated address spaces for processes.
    Memory Regions and Permissions: Define what actions (read, write, execute) can be performed on specific memory areas.
    Segmentation and Paging: Techniques used by the OS to manage and protect memory.
virtual / physical memory
Explain disadvantages of std::make_shared over std::shared_ptr construction from plain C++ pointer.
    1.Single Allocation for Object and Control Block  can be a disadvantage if you want to separate the lifetimes of the control block and the managed object. For instance, if you want to manually delete the object but keep the control block alive (perhaps to hold weak references), this is not possible with std::make_shared since the control block and the object share the same allocation.
    2.Increased Memory Usage in Some Cases
    3.Inability to Use Custom Deleters
caching, precaching, lazy caching concepts
cache hit/miss
memory fragmentation avoidance
How to make vector move elements =>vec[0] = std::move(vec[2]);
What is the difference between std::move and std::forward?
    std::move and std::forward are both utility functions provided by the C++ Standard Library, primarily for use in move semantics and perfect forwarding.
lambda which accepts one variable by value and one by reference -> [=,&](){}
constexpr variables/functions
    A constexpr variable is one that can be evaluated at compile time
    A constexpr function can be evaluated at compile time if all arguments are constant expressions. Otherwise, it behaves like a regular function evaluated at runtime.
lvalue vs rvalue
Move semantics
    Move semantics is a feature in C++ that enables efficient transfer of resources from one object to another
    Move semantics is facilitated by rvalue references and the std::move function.
    #include <iostream>
#include <utility>

class Resource {
public:
    int* data;

    // Constructor
    Resource(size_t size) : data(new int[size]) {
        std::cout << "Resource acquired\n";
    }

    // Destructor
    ~Resource() {
        delete[] data;
        std::cout << "Resource destroyed\n";
    }

    // Move constructor
    Resource(Resource&& other) noexcept : data(other.data) {
        other.data = nullptr;  // Nullify the source's data pointer
        std::cout << "Resource moved\n";
    }

    // Move assignment operator
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            delete[] data;       // Release current resource
            data = other.data;   // Transfer ownership
            other.data = nullptr; // Nullify the source's data pointer
            std::cout << "Resource moved via assignment\n";
        }
        return *this;
    }

    // Copy constructor and copy assignment operator are deleted
    Resource(const Resource&) = delete;
    Resource& operator=(const Resource&) = delete;
};

int main() {
    Resource res1(10);            // Resource acquired
    Resource res2 = std::move(res1); // Resource moved

    Resource res3(20);            // Resource acquired
    res3 = std::move(res2);       // Resource moved via assignment

    return 0; // Resource destroyed (for res3), Resource destroyed (for res1 and res2, with null data)
}

linker vs loader
Type-traits
    Type traits in C++ are a set of templates used to provide information about types at compile time. They are part of the <type_traits> header and are heavily utilized in template metaprogramming. Type traits can help determine properties of types, such as whether a type is an integer, a pointer, or a class. They can also modify types, such as removing const qualifiers or adding references.
    std::cout << "Type: " << typeid(T).name() << "\n";
    std::cout << "Is integral: " << std::is_integral<T>::value << "\n";
    std::cout << "Is floating point: " << std::is_floating_point<T>::value << "\n";
    std::cout << "Is pointer: " << std::is_pointer<T>::value << "\n";
    std::cout << "Is reference: " << std::is_reference<T>::value << "\n";
    std::cout << "Is array: " << std::is_array<T>::value << "\n";
    std::cout << "Is class: " << std::is_class<T>::value << "\n";
    std::cout << "Is same as int: " << std::is_same<T, int>::value << "\n";
    std::cout << "Removing const: " << typeid(typename std::remove_const<T>::type).name() << "\n";
    std::cout << "Adding pointer: " << typeid(typename std::add_pointer<T>::type).name() << "\n";

Concepts:
C++20 introduced the concept of "concepts," which are a way to specify constraints on template parameters. Concepts make templates easier to use and debug by providing clear and precise requirements for the types that can be used as template arguments. They allow for more readable and maintainable code and provide better error messages when template instantiation fails.

#include <concepts>
#include <iostream>

template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

template<Addable T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(1, 2) << std::endl;     // OK
    std::cout << add(1.1, 2.2) << std::endl; // OK
    // std::cout << add("Hello, ", "world!") << std::endl; // The result of adding two const char* is not a const char* but an std::string
    return 0;
}

Functor
    a functor (short for "function object") is an object that can be called as if it were a function. Essentially, a functor is any object that overloads the operator(), allowing it to be used in places where functions are typically expected.
    class Compare {
    public:
        bool operator()(int a, int b) const {
            return a < b; // Define a comparison (less than)
        }
    };
    std::sort(numbers.begin(), numbers.end(), Compare());

static vs dynamic lib
Which class methods are defined implicitly?=>Constr,Destr,CopyConstr,Assignment Operator,MoveConstr,MoveAssignment Operator
inline functions. Is inlining of functions marked with "inline" guaranteed?
    In C++, the inline keyword is used to suggest to the compiler that a function should be expanded in place, rather than being invoked through a function call. However, marking a function as inline does not guarantee that the function will actually be inlined
Static, const, mutable keywords
    When used with class data members, static means that the data member is shared among all instances of the class. There is only one copy of the static data member, regardless of how many objects of the class are created.
    Static member functions belong to the class rather than any particular object. They can only access static data members and other static member functions of the class.
    The const keyword indicates that a variable or data member's value cannot be changed after its initialization. 
    A member function declared as const promises not to modify any member variables of the class.
    The mutable keyword allows a member variable of a class to be modified even in a const member function.
macros
basic instructions (for/while ...)
preprocessing vs compiling vs linking
variables scope
pointers vs reference argument passing
Priority inversion
Thread Pooling
Inter Process Communication
Synchronization mechanisms - std::atomics and memory order sequence, std::condition_variable
Explain std::future and std::promise 
    A std::promise is an object that allows you to set a value (or an exception) that will be available in the future.It is used to provide a value to a std::future.Once the value is ready, the std::promise is used to set the value, which can then be retrieved through the associated std::future.
    A std::future is an object that can retrieve the value set by a std::promise.The std::future provides a get() method that blocks until the value is available, ensuring that the result is retrieved once it is ready.
Fork
Synchronization mechanisms - semaphores, mutexes

Can you please explain "Builder" design pattern?
Describe difference between adapter and decorator
Describe difference between abstract factory and builder
CRTP
Can you please explain "FlyWeight" design pattern?
Policy-based design
Can you please explain “bridge”, "adapter" design pattern?
Composition vs Aggregation vs Inheritence.Which one do you prefer Composition or Aggregation?
    composition and aggregation are types of associations that describe the relationships between classes. Both are forms of has-a relationships.Inheritence describes 'is-a' relationship between classes.

    Composition represents a strong ownership relationship between two classes. In composition, the lifetime of the contained object is dependent on the lifetime of the container object. When the container object is destroyed, the contained objects are also destroyed.
    Ex: House has a room and when House is destroyed, room will be destroyed too Also, a room cannot belong to more than 1 house.

    Aggregation represents a weaker association where one class (the container) holds a reference or pointer to another class (the component), but the component's lifetime is not strictly tied to the container's lifetime. Aggregation represents a has-a relationship where the contained objects can exist independently of the container.Aggregation represents a 'part-of' relationship
    For example, a car has an engine, but the engine can exist independently of the car.

    Inheritance establishes a parent-child relationship between classes. The derived class inherits attributes and behaviors from the base class.
    Ex:Dog is a Animal

    Favor Composition Over Inheritance: This is a common design principle. Composition is generally preferred because it offers greater flexibility and helps avoid the pitfalls of tight coupling and fragile hierarchies. It allows you to build systems with interchangeable components, which can be more easily modified or extended.

    When Inheritance Makes Sense: Use inheritance when you have a well-defined hierarchy, where subclasses share common behavior and an "is-a" relationship makes sense. Inheritance is particularly useful when you need polymorphism.

Creational Patterns (Singleton, Factory, Builder) 
Give an insight into such patterns as Façade/Proxy/Decorator/Strategy/Observer (selectively)

How to get list of running processes?
Describe grep / tail / less / more
Describe difference between TCP and UDP
    Feature                 TCP                                         UDP
    Connection Type         Connection-oriented (requires handshake)    Connectionless (no handshake)
    Reliability             Reliable (error checking, retransmissions)  Unreliable (no guarantees)
    Order of Data           Ordered (packets arrive in sequence)        Unordered (packets may arrive out of order)
    Speed                   Slower due to overhead                      Faster due to minimal overhead
    Use Cases               Web browsing, file transfers, emails        Streaming, gaming, VoIP, DNS
    Flow & Congestion Control   Yes                                     No
    Header Size             Larger (20 bytes)                           Smaller (8 bytes)
How to find out free space on the disk? (df)
How to find out a size of a directory? (du)

Difference between exception handling and error handling. Which one would you choose for your project and why.
    Exception Handling is generally preferable for modern, high-level applications where clean, maintainable code is a priority and where the overhead of exceptions is acceptable.
    Error Handling might be more appropriate for performance-critical code, simpler error scenarios, or environments where exceptions are not supported or where you need finer control over how errors are handled and propagated.

exceptions vs mutex
What is the purpose of mocking in relation to unit testing
What frameworks related to unit testing did you use
Difference between acceptance test and functional test?
What percentage of code coverage do you think is appropriate for unit testing?
What is Unit test, Integration Test, Smoke test, Regression Test and what are the differences between them?
**Unit Testing: Tests individual components or functions.
**Integration Testing: Tests interactions between integrated units.
**System Testing: Tests the complete, integrated system.
**Acceptance Testing: Validates the system against user requirements.
**Performance Testing: Assesses system speed and responsiveness.
**Load Testing: Tests system behavior under expected load.
**Stress Testing: Tests system limits under extreme conditions.
**Usability Testing: Evaluates user-friendliness and interface.
**Compatibility Testing: Ensures compatibility with different environments.
**Regression Testing: Checks for new bugs after changes.
**Security Testing: Identifies vulnerabilities and risks.
**Alpha Testing: Internal testing by developers before public release.
**Smoke Testing: Preliminary testing to check basic functionality
**Sanity Testing: Quick checks to confirm specific functionalities work after changes.


Static Anaysis:cppcheck can be used
Documentation:doxygen


CopyConstr and Assignment Operator
==================================
When no copy constructor is explicitly defined, the compiler provides a default copy constructor. This default copy constructor performs a shallow copy(This type of copy duplicates the top-level structure of an object but does not duplicate the resources it points to. Essentially, it copies the pointer values, meaning that both the original and the copied object share the same resources)

class MyClass {
public:
    int* data;

    // Constructor
    MyClass(int value) : data(new int(value)) {}

    // Copy constructor for deep copy
    MyClass(const MyClass& other) : data(new int(*other.data)) {}

    // Copy assignment operator for deep copy
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {
            delete data;        // Release the current resource
            data = new int(*other.data); // Copy the resource
        }
        return *this;
    }

    // Destructor
    ~MyClass() {
        delete data;
    }
};


O(1)<<O(log n)<<O(n)<<O(n log n)<<O(n2)

Uniform initialization
======================
With C++11, everything can be initialized in much the same way.

Initialization of dynamically allocated arrays:
int *pi = new int[5]{1, 2, 3, 4, 5};
Initialization of an array member variable:
class A {
  int arr[3];
public:
  A(int x, int y, int z) : arr{x, y, z} { };
};
Initialization of a STL container:
 std::vector v1{1, 2};
Implicitly initialize objects to return:
return {foo, bar};
Implicitly initialize a function parameter:
f({foo, bar});
there are differences in terms of priorities, it's set in this order:
initializer_list
regular constructor
aggregate initialization


SFINAE (Substitution Failure Is Not An Error)
==============================================
SFINAE is a principle of the C++ programming language that states that a compiler should not fail to compile a program just because it cannot substitute a template parameter. This principle allows for the use of template metaprogramming and enables the compiler to make decisions based on the types of template arguments, which can be useful when dealing with complex code and difficult to reason about logic.

Template MetaProgramming
========================
Template metaprogramming is a powerful feature in C++ that allows you to write code that is both flexible and efficient. It enables computations and decisions to be made at compile time, which can lead to significant performance improvements. However, TMP can also be complex and difficult to debug, so it’s essential to use it judiciously and where it provides clear benefits.

Memory Layout in C
In the C programming language, memory layout refers to how variables, arrays, structs, and other data types are stored in memory. Memory is typically divided into four main sections for a running C program:

Text (Code) Segment:

Contains the compiled machine code of the program (the instructions that the CPU executes).
This segment is usually read-only to prevent accidental modification of the code.
Data Segment:

This segment stores initialized global and static variables.
Divided into two parts:
Read-only data: For constants and global variables marked const.
Writable data: For initialized global and static variables.
BSS (Block Started by Symbol) Segment:

Contains uninitialized global and static variables (which are automatically initialized to zero).
It is zeroed out when the program starts.
Heap Segment:

Used for dynamic memory allocation (e.g., when using malloc).
Grows upwards as more memory is dynamically allocated.
Stack Segment:

Stores local variables, function call parameters, return addresses, and the function call stack.
Grows downwards (towards lower memory addresses).
Stack frames are created for each function call, containing the local variables and function return addresses.

Difference between nullptr and void pointer
===========================================
A null pointer is a pointer that does not point to any valid memory location. It is used to indicate that a pointer is intentionally pointing to "nothing."
A void pointer is a type of pointer that can point to any data type but doesn’t have a type associated with it. You cannot dereference a void* directly because the compiler doesn't know the type of data it points to.

Stack Overflow:
==============
A stack overflow occurs when a program exhausts the stack memory, which is a fixed-size block of memory used to store information about active functions and their variables during program execution. This can happen when a program uses more stack space than is available, leading to a crash or unpredictable behavior.

Difference between malloc and calloc:
====================================
malloc(size_t size): Allocates a single block of memory of the specified size in bytes.Does not initialize the allocated memory. The contents of the memory block are indeterminate (may contain garbage values).Faster than calloc
calloc(size_t num, size_t size): Allocates memory for an array of num elements, each of the specified size, and initializes all allocated memory to zero.



Static Library Vs Dynamic Library
=====================================================
Linking Time                Compile-time                     Runtime
File Extension              .lib, .a                        .dll, .so
Executable Size             Larger (contains library code)  Smaller (references library)
Performance                 Faster startup                  Slightly slower startup
Updates                     Must recompile to update        Updates without recompilation
Dependency Management       No external dependencies        Can share libraries between apps


NetApp:

CAP Theorem:
===========
The CAP theorem (also known as Brewer's theorem) is a fundamental principle in distributed systems that describes the trade-offs between three properties: Consistency, Availability, and Partition Tolerance. According to the theorem, a distributed system can only guarantee at most two of these three properties at the same time.
"You can pick two: Consistency, Availability, or Partition Tolerance."

RAII:
====
RAII is a programming idiom in C++ that ties the lifecycle of a resource (e.g., memory, file handles, network sockets) to the lifetime of an object. The idea is to acquire resources in a constructor and release them in a destructor, ensuring proper cleanup even if exceptions occur.

Key Principles of RAII:
Automatic Resource Management:

Resources are acquired when an object is created (constructor).
Resources are released when the object goes out of scope (destructor).
Exception Safety:

If an exception is thrown, the destructor is guaranteed to be called, preventing resource leaks.
No Manual Cleanup:

Avoids the need for explicit cleanup code, such as calling delete or close.
Common Examples of RAII in C++:
1. Memory Management:
Modern C++ uses smart pointers like std::unique_ptr and std::shared_ptr for automatic memory management.

2. File Handling:
RAII can be applied to file operations to ensure files are closed properly.

3. Mutex Locking:
RAII is crucial in multithreaded environments to ensure that locks are released properly, even if exceptions are thrown.

4. Custom Resource Management:
RAII can be applied to custom resources like sockets or database connections.

Practical Experience:
"I used RAII to manage database connections by creating a wrapper class that ensured the connection was automatically closed when the object went out of scope, preventing leaks."

